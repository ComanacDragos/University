--CREATE DATABASE Ex5
GO
USE Ex5
GO

DROP TABLE Visits
DROP TABLE Quotas
DROP TABLE Visitors
DROP TABLE Foods
DROP TABLE Animals
DROP TABLE Zoos

GO

CREATE Table Zoos(
	zooId INT PRIMARY KEY,
	name VARCHAR(100),
	admin VARCHAR(100)
)

CREATE Table Animals(
	animalId INT PRIMARY KEY,
	name VARCHAR(100),
	DOB DATE,
	zooId INT FOREIGN KEY REFERENCES Zoos(zooId)
)

CREATE Table Foods(
	foodId INT PRIMARY KEY,
	name VARCHAR(100),
)


CREATE Table Visitors(
	visitorId INT PRIMARY KEY,
	name VARCHAR(100),
	age INT
)

CREATE TABLE Quotas(
	quotaId INT PRIMARY KEY IDENTITY(1,1),
	animalId INT FOREIGN KEY REFERENCES Animals(animalId),
	foodId INT FOREIGN KEY REFERENCES Foods(foodId),
	pieces INT
)

CREATE TABLE Visits(
	visitId INT PRIMARY KEY IDENTITY(1,1),
	zooId INT FOREIGN KEY REFERENCES Zoos(zooId),
	visitorId INT FOREIGN KEY REFERENCES Visitors(visitorId),
	price INT,
	visitDay DATE
)
GO

INSERT INTO Foods (foodId) VALUES (1), (2), (3)

INSERT INTO Visitors(visitorId) VALUES (1),(2),(3)

INSERT INTO Zoos (zooId) VALUES (1),(2),(3)

INSERT INTO Animals(animalId, zooId) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 2),
(5, 2),
(6, 3)

INSERT INTO Visits(visitorId, zooId)VALUES
(1, 1),
(2, 2),
(3, 3),
(3,3)

INSERT INTO Quotas(animalId, foodId) VALUES
(1,1),
(1,2),
(2,1)
GO

CREATE OR ALTER PROC delete_quotas(@animalId INT)
AS
	IF NOT EXISTS (SELECT * FROM Animals WHERE animalId = @animalId)
	BEGIN
		RAISERROR('Animal does not exist', 16,1)
		RETURN
	END
	DELETE FROM Quotas
	WHERE animalId = @animalId
GO

delete_quotas 1

SELECT * FROM Quotas

GO

CREATE VIEW smallest_nr_visits AS
SELECT Z.zooId
FROM Zoos Z INNER JOIN Visits V ON Z.zooId = V.zooId
GROUP BY Z.zooId
HAVING COUNT(*) = (
		SELECT MIN(C.visits)
		FROM
			(
			SELECT COUNT(*) AS 'visits'
			FROM Zoos Z INNER JOIN Visits V ON Z.zooId = V.zooId
			GROUP BY Z.zooId
			) C
		)
GO
SELECT * FROM smallest_nr_visits

GO

CREATE FUNCTION visitors_to_zoos(@N INT)
RETURNS TABLE
AS
RETURN 
	SELECT DISTINCT V.visitorId
	FROM Visitors V INNER JOIN Visits V2 ON V.visitorId = V2.visitorId
	WHERE V2.zooId IN (
			SELECT Z.zooId
			FROM Zoos Z INNER JOIN Animals A ON Z.zooId = A.zooId
			GROUP BY Z.zooId
			HAVING COUNT(*) >=@N
			)
GO
SELECT * FROM visitors_to_zoos(1)
SELECT * FROM visitors_to_zoos(2)
SELECT * FROM visitors_to_zoos(3)
