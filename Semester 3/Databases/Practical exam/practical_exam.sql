--CREATE DATABASE PracticalExam
GO
USE PracticalExam
GO

DROP TABLE Rides
DROP TABLE Riders
DROP TABLE Stations
DROP TABLE Scooters
DROP TABLE ScooterProviders

GO
--a
CREATE TABLE ScooterProviders(
	providerId INT PRIMARY KEY,
	name VARCHAR(100),
	turnover VARCHAR(100),
	foundingDate DATE
)

CREATE TABLE Scooters(
	scooterId INT PRIMARY KEY,
	providerId INT FOREIGN KEY REFERENCES ScooterProviders(providerId),
	serial VARCHAR(100),
)

CREATE TABLE Stations(
	stationId INT PRIMARY KEY,
	street VARCHAR(100),
	nr INT,
	city VARCHAR(100)
)

CREATE TABLE Riders(
	riderId INT PRIMARY KEY,
	name VARCHAR(100),
	age INT
)

CREATE TABLE Ride(
	rideId INT PRIMARY KEY IDENTITY(1,1),
	scooterId INT FOREIGN KEY REFERENCES Scooters(scooterId),
	riderId INT FOREIGN KEY REFERENCES Riders(riderId),
	pickUp INT FOREIGN KEY REFERENCES Stations(stationId),
	dropOff INT FOREIGN KEY REFERENCES Stations(stationId),
	rideStart DATETIME,
	rideEnd DATETIME,
	price INT
)
/* I chosed to have rideId so that one rider can ride the same scooter from and
to the same stations multiple times
I chosed to have pickUp and pickOff in the Ride table so that one ride
has only one pickUp and one pickOff
*/
GO

INSERT INTO ScooterProviders (providerId, name) VALUES
(1, 'p1'),(2, 'p2'),(3, 'p3')

INSERT INTO Scooters (scooterId, providerId) VALUES
(1, 1),
(2, 1),
(3, 1),
(4, 2),
(5, 2),
(6, 3)

INSERT INTO Stations (stationId) VALUES
(1), (2),(3)

INSERT INTO Riders(riderId, name) VALUES
(1, 'n1'),(2, 'n2'),(3, 'n3'),(4, 'n4')
GO

GO

--b
CREATE OR ALTER PROC add_ride (
	@rider VARCHAR(100),
	@scooterId INT,
	@pickUp INT,
	@dropOff INT,
	@start DATETIME,
	@end DATETIME,
	@price INT)
AS
	IF NOT EXISTS (SELECT * FROM Riders WHERE @rider = name)
	BEGIN
		RAISERROR('Rider does not exist', 16,1)
		RETURN
	END

	IF NOT EXISTS (SELECT * FROM Scooters WHERE @scooterId = scooterId)
	BEGIN
		RAISERROR('Scooter does not exist', 16,1)
		RETURN
	END

	IF NOT EXISTS (SELECT * FROM Stations WHERE @pickUp = stationId)
	BEGIN
		RAISERROR('Pickup does not exist', 16,1)
		RETURN
	END

	IF NOT EXISTS (SELECT * FROM Stations WHERE @dropOff = stationId)
	BEGIN
		RAISERROR('DropOff does not exist', 16,1)
		RETURN
	END

	DECLARE @riderId INT
	SELECT @riderId = riderId FROM Riders WHERE @rider = name

	IF NOT EXISTS (SELECT * FROM Ride WHERE @riderId = riderId 
										AND @start = rideStart
										AND @end = rideEnd
										)
	BEGIN 
		INSERT INTO Ride (scooterId, riderId, pickUp, dropOff, rideStart, rideEnd, price) VALUES
		(@scooterId, @riderId, @pickUp, @dropOff, @start, @end, @price)
	END
	ELSE
	BEGIN
		UPDATE Ride 
		SET price = @price, 
			scooterId = @scooterId,
			pickUp = @pickUp,
			dropOff = @dropOff
		WHERE rideId = (SELECT rideId WHERE @riderId = riderId 
										AND @start = rideStart
										AND @end = rideEnd
										)
	END
GO
add_ride 'n11', 1, 1, 1, '1-1-2020 10:15', '1-1-2020 10:20', 10
add_ride 'n1', 11, 1, 1, '1-1-2020 10:15', '1-1-2020 10:20', 10
add_ride 'n1', 1, 11, 1, '1-1-2020 10:15', '1-1-2020 10:20', 10
add_ride 'n1', 1, 1, 11, '1-1-2020 10:15', '1-1-2020 10:20', 10


add_ride 'n1', 1, 1, 1, '1-1-2020 10:15', '1-1-2020 10:20', 10
add_ride 'n1', 2, 2, 2, '1-1-2020 10:15', '1-1-2020 10:20', 20


add_ride 'n1', 1, 1, 1, '1-1-2020 10:50', '1-1-2020 10:59', 10


add_ride 'n2', 1, 1, 1, '1-2-2020 10:50', '1-2-2020 10:59', 10

add_ride 'n3', 1, 1, 1, '1-3-2020 10:50', '1-3-2020 10:59', 10

DELETE FROM Ride

SELECT * FROM Ride

GO

--c
GO
CREATE VIEW veryActiveRidersView 
AS
SELECT name
FROM Riders
WHERE riderId IN(
	SELECT riderId
	FROM Ride
	GROUP BY riderId
	HAVING COUNT(*) >(
		SELECT AVG(R.NoRides) RideAverage
		FROM (
			SELECT COUNT(*) + 0.0 AS NoRides --+0.0 does the conversion to float
			FROM Ride
			GROUP BY riderId
		) R
	)
)
GO
SELECT * FROM veryActiveRidersView

GO
--d

CREATE FUNCTION providers_with_scooters (@S INT)
RETURNS TABLE
AS
RETURN 
	SELECT P.name
	FROM ScooterProviders P INNER JOIN Scooters S ON P.providerId = S.providerId
	GROUP BY P.providerId, P.name
	HAVING COUNT(*) >= @S
GO
SELECT * FROM Scooters

SELECT * FROM providers_with_scooters(1)
SELECT * FROM providers_with_scooters(2)
SELECT * FROM providers_with_scooters(3)