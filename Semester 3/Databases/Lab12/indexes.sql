--CREATE DATABASE TestIndexes
--GO
USE TestIndexes

/*
Work on 3 tables of the form Ta(aid, a2, …), Tb(bid, b2, …), Tc(cid, aid, bid, …), where:

aid, bid, cid, a2, b2 are integers;
the primary keys are underlined;
a2 is UNIQUE in Ta;
aid and bid are foreign keys in Tc, referencing the primary keys in Ta and Tb, respectively.
*/

--DROP TABLE Ta
CREATE TABLE Ta(
	aid INTEGER PRIMARY KEY,
	a2 INTEGER UNIQUE,
	a3 INTEGER
);

--DROP PROCEDURE sp_insert_Ta
GO
CREATE PROCEDURE sp_insert_Ta @seed INTEGER
AS
BEGIN
	INSERT INTO Ta (aid, a2, a3) VALUES
	(@seed, 2*@seed+1, 2*@seed)
END
GO

sp_populate_table 'Ta', 50000

--DROP TABLE Tb
CREATE TABLE Tb(
	bid INTEGER PRIMARY KEY,
	b2 INTEGER,
	b3 INTEGER
);

--DROP PROCEDURE sp_insert_Tb
GO
CREATE PROCEDURE sp_insert_Tb @seed INTEGER
AS
BEGIN
	INSERT INTO Tb (bid, b2, b3) VALUES
	(@seed, @seed-1, @seed + 1)
END
GO

sp_populate_table 'Tb', 100000

--DROP TABLE Tc
CREATE TABLE Tc(
	cid INTEGER PRIMARY KEY,
	aid INTEGER FOREIGN KEY REFERENCES Ta(aid),
	bid INTEGER FOREIGN KEY REFERENCES Tb(bid),
);

--DROP PROCEDURE sp_insert_Tc
GO
CREATE PROCEDURE sp_insert_Tc @seed INTEGER
AS
BEGIN
	INSERT INTO Tc (cid, aid, bid) VALUES
	(@seed,
	(SELECT TOP 1 aid FROM Ta ORDER BY NEWID()),
	(SELECT TOP 1 bid FROM Tb ORDER BY NEWID())
	)
	PRINT @seed
END
GO

sp_populate_table 'Tc', 1000

SELECT * FROM Ta
SELECT * FROM Tb
SELECT * FROM Tc
-- a. Write queries on Ta such that their execution plans contain the following operators:

--clustered index scan;

SELECT * FROM Ta
--because all rows and columns are selected

--clustered index seek;

SELECT * FROM Ta WHERE aid = 1
--because we filter by the pk

--nonclustered index scan;

SELECT a2 FROM Ta
--because we select only the column on which there is a non clustered index

--nonclustered index seek;

SELECT a2 FROM Ta WHERE a2 = 1
--because we select and filter by the only the column on which there is a non clustered index

--key lookup.

SELECT a3 FROM Ta WHERE a2 = 2
--we filter by a column on which there is a non clustered index but we select a column on which there is no clustered index

--b. Write a query on table Tb with a WHERE clause of the form WHERE b2 = value and analyze its execution plan. 

--ALTER INDEX indx_ncl_b2 ON Tb DISABLE
--ALTER INDEX indx_ncl_b2 ON Tb REBUILD

SELECT * FROM Tb WHERE b2 = 90000
--without index:
--clustered index scan
--0.006s

--Create a nonclustered index that can speed up the query. Examine the execution plan again.

CREATE NONCLUSTERED INDEX indx_ncl_b2 ON Tb(b2)

SELECT * FROM Tb WHERE b2 = 90000
--with index
--index seek non clustered on indx_ncl_b2 then a key lookup(clustered)
--0.000s

--c. Create a view that joins at least 2 tables.

--DROP VIEW my_view
GO
CREATE VIEW my_view AS
SELECT Tc.cid, Ta.aid, Tb.bid, Ta.a2, Tb.b2
FROM Tc 
INNER JOIN Ta ON Tc.aid = Ta.aid
INNER JOIN Tb ON Tc.bid = Tb.bid
GO

--Check whether existing indexes are helpful; if not, reassess existing indexes / examine the cardinality of the tables.

DBCC DROPCLEANBUFFERS

DBCC FREEPROCCACHE

SELECT b2  FROM my_view WHERE b2 = 90000
--0.000s with indx_ncl_b2
--0.007s without indx_nclb2


--0.3868
--0.03