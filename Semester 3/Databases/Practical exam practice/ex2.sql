--CREATE DATABASE Ex2
--GO
USE Ex2
GO

DROP TABLE Sells
DROP TABLE ShoeShops
DROP TABLE Women
DROP TABLE Shops
DROP TABLE Shoes
DROP TABLE ShoeModels
GO
--a
CREATE TABLE ShoeModels(
	modelId INT PRIMARY KEY,
	name VARCHAR(100),
	season VARCHAR(100)
)

CREATE TABLE Shoes(
	shoeId INT PRIMARY KEY,
	price INT,
	modelId INT FOREIGN KEY REFERENCES ShoeModels(modelId)
)

CREATE TABLE Shops(
	shopId INT PRIMARY KEY,
	name VARCHAR(100),
	city VARCHAR(100)
)

CREATE TABLE Women(
	womanId INT PRIMARY KEY,
	name VARCHAR(100),
	amount INT
)

CREATE TABLE ShoeShops(
	shoeId INT FOREIGN KEY REFERENCES Shoes(shoeId),
	shopId INT FOREIGN KEY REFERENCES Shops(shopId),
	quantity INT,
	CONSTRAINT pk_shoe_shops PRIMARY KEY (shoeId, shopId)
)
	

CREATE TABLE Sells(
	sellId INT PRIMARY KEY IDENTITY(1,1),
	womanId INT FOREIGN KEY REFERENCES Women(womanId),
	shoeId INT NOT NULL,
	shopId INT NOT NULL,
	CONSTRAINT fk_shoe_shops FOREIGN KEY (shoeId, shopId) REFERENCES ShoeShops(shoeId, shopId),
	noShoes INT,
	amount INT
)



INSERT INTO ShoeModels (modelId, name)VALUES
(1,'m1'),
(2,'m2'),
(3,'m3')

INSERT INTO Shoes (shoeId, price, modelId)VALUES
(1, 10, 1),
(2, 10, 1),
(3, 20, 2),
(4, 30, 3),
(5, 40, 3)

INSERT INTO Shops (shopId, name)VALUES
(1,'s1'),
(2,'s2'),
(3,'s3')

DELETE FROM Women
INSERT INTO Women (womanId, name)VALUES
(1,'n1'),(2,'n2'),(3,'n3'),(4,'n4')

--INSERT INTO Sells(womanId, shoeId, shopId,noShoes)
--(1,


SELECT * FROM ShoeModels
SELECT * FROM Shoes
SELECT * FROM Shops
SELECT * FROM Women


--b
GO
CREATE OR ALTER PROC add_shoe(@shoeId INT, @shop VARCHAR(100), @quantity INT)
AS
	IF NOT EXISTS (SELECT * FROM Shoes WHERE shoeId = @shoeId)
	BEGIN
		RAISERROR('Shoe does not exists.',16,1)
		RETURN
	END
	
	IF NOT EXISTS (SELECT * FROM Shops WHERE name = @shop)
	BEGIN
		RAISERROR('Shop does not exists.',16,1)
		RETURN
	END
	
	IF @quantity <=0
	BEGIN
		RAISERROR('Quantity must be a strictily positive number.',16,1)
		RETURN
	END
	
	INSERT INTO ShoeShops (shoeId, shopId, quantity)VALUES
	(@shoeId,
	(SELECT shopId FROM Shops WHERE name = @shop),
	@quantity
	)
GO

EXEC add_shoe 1, 's1', 10
EXEC add_shoe 1, 's2', 10
EXEC add_shoe 1, 's3', 10
EXEC add_shoe 2, 's1', 10
EXEC add_shoe 2, 's2', 10
EXEC add_shoe 3, 's1', 10




SELECT * FROM ShoeShops

--c 
DELETE FROM Sells
INSERT INTO Sells (womanId, shoeId,shopId,noShoes)VALUES
(4, 1, 1, 1),
(1, 1, 1, 1),
(1, 2, 1, 1),
(2, 1, 2, 2),
(3, 3, 1,3)

SELECT * FROM Sells

GO
CREATE VIEW women_with_shoes
AS
SELECT name
FROM Women W INNER JOIN( 
		SELECT womanId
		FROM Sells
		WHERE shoeId IN (
				SELECT S.shoeId
				FROM ShoeModels SM INNER JOIN Shoes S ON SM.modelId = S.modelId
				WHERE SM.name = 'm1'
			)
		GROUP BY womanId
		HAVING SUM(noShoes)>=2
	) WID ON W.womanId = WID.womanId
GO

SELECT * FROM women_with_shoes
--d
GO
CREATE FUNCTION shoes_in_shops(@T INT)
RETURNS TABLE
AS
RETURN
	SELECT S.shoeId
	FROM Shoes S INNER JOIN ShoeShops SS ON S.shoeId = SS.shoeId
	GROUP BY S.shoeId
	HAVING COUNT(*)>= @T
GO

SELECT * FROM shoes_in_shops(1)
SELECT * FROM shoes_in_shops(2)
SELECT * FROM shoes_in_shops(3)
SELECT * FROM shoes_in_shops(4)
