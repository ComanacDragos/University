--CREATE DATABASE Ex4
GO
USE EX4
GO

DROP TABLE ChefCakes
DROP TABLE OrderDetails
DROP TABLE Cakes
DROP TABLE CakeTypes
DROP TABLE Chefs
DROP TABLE Orders

GO

CREATE TABLE Orders(
	orderId INT PRIMARY KEY,
	orderDate DATE
)

CREATE TABLE Chefs(
	chefId INT PRIMARY KEY,
	name VARCHAR(100),
	gender CHAR,
	DOB date
)

CREATE TABLE CakeTypes(
	typeId INT PRIMARY KEY,
	name VARCHAR(100),
	description VARCHAR(200)
)

CREATE TABLE Cakes(
	cakeId INT PRIMARY KEY,
	name VARCHAR(100),
	shape VARCHAR(100),
	weight INT,
	price INT,
	typeId INT FOREIGN KEY REFERENCES CakeTypes(typeId)
)

CREATE TABLE OrderDetails(
	orderId INT FOREIGN KEY REFERENCES Orders(orderId),
	cakeId INT FOREIGN KEY REFERENCES Cakes(cakeId),
	pieces INT,
	CONSTRAINT pk_order_details PRIMARY KEY (orderId, cakeId)
)

CREATE TABLE ChefCakes(
	chefId INT FOREIGN KEY REFERENCES Chefs(chefId),
	cakeId INT FOREIGN KEY REFERENCES Cakes(cakeId),
	CONSTRAINT pk_chef_cakes PRIMARY KEY (chefId, cakeId)
)

GO

INSERT INTO Chefs (chefId, name) VALUES
(1, 'n1'),
(2, 'n2'),
(3, 'n3')

INSERT INTO CakeTypes (typeId) VALUES
(1),(2),(3)

INSERT INTO Cakes(cakeId, name, typeId) VALUES
(1, 'c1', '1'),
(2, 'c2', '2'),
(3, 'c3', '3')

INSERT INTO ChefCakes (chefId, cakeId) VALUES
(1,1),
(1,2),
(1,3),
(2,1),
(2,2),
(2,3),
(3,1),
(3,2)

INSERT INTO Orders(orderId)VALUES (1), (2),(3)

GO
CREATE OR ALTER PROC add_cake(@orderId INT, @cake VARCHAR(100), @P INT)
AS
	IF NOT EXISTS (SELECT * FROM Orders WHERE @orderId = orderId)
	BEGIN
		RAISERROR('Order does not exist', 16,1)
		RETURN
	END

	IF NOT EXISTS (SELECT * FROM Cakes WHERE @cake = name)
	BEGIN
		RAISERROR('Cake does not exist', 16,1)
		RETURN
	END

	DECLARE @cakeId INT
	SELECT @cakeId = cakeId FROM Cakes WHERE @cake = name

	IF NOT EXISTS (SELECT * FROM OrderDetails WHERE cakeId = @cakeId AND orderId = @orderId)
	BEGIN
		INSERT INTO OrderDetails (orderId, cakeId, pieces) VALUES
		(@orderId, @cakeId, @P)
	END
	ELSE
	BEGIN 
		UPDATE OrderDetails 
		SET pieces = @P
		WHERE cakeId = @cakeId AND orderId = @orderId
	END
GO

add_cake 5, 'c1', 5

add_cake 1, 'c24', 5

add_cake 1, 'c1', 2

add_cake 1, 'c1', 5

add_cake 2, 'c1', 531

SELECT * FROM OrderDetails

GO

SELECT C.name
FROM Chefs C INNER JOIN ChefCakes CC ON C.chefId = CC.chefId
GROUP BY C.chefId, C.name
HAVING COUNT(*)>= (SELECT COUNT(*) FROM Cakes)
