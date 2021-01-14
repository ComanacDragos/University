CREATE DATABASE Seminar6
GO
USE Seminar6
GO

--a)

CREATE TABLE TrainTypes(
	typeId INT PRIMARY KEY,
	typeName VARCHAR(50)
);

INSERT INTO TrainTypes VALUES
(1, 'abur'),
(2, 'electric');

CREATE TABLE Trains(
	trainId int PRIMARY KEY,
	name VARCHAR(50),
	typeId INT FOREIGN KEY REFERENCES TrainTypes(typeId)
);

INSERT INTO Trains VALUES
(1, 'train1', 1),
(2, 'train2', 2),
(3, 'train3', 1),
(4, 'train4', 2);


CREATE TABLE Stations(
	stationId INT PRIMARY KEY,
	stationName VARCHAR(50) UNIQUE
);

INSERT INTO Stations VALUES
(1, 'Cluj'),
(2, 'Mures'),
(3, 'Bucuresti'),
(4, 'Iasi');

CREATE TABLE Routes(
	routeId INT PRIMARY KEY,
	routeName VARCHAR(50) UNIQUE,
	trainId INT FOREIGN KEY REFERENCES Trains(trainId)
);

INSERT INTO Routes VALUES
(3, 'Cluj-Iasi-Bucuresti',3)
(1, 'Cluj-Iasi', 1),
(2,'Cluj-Bucuresti', 2);


CREATE TABLE StationRoutes(
	routeId INT FOREIGN KEY REFERENCES Routes(routeId),
	stationId INT FOREIGN KEY REFERENCES Stations(stationId),
	arrival TIME,
	departure TIME,
	CONSTRAINT pk_stationRoutes PRIMARY KEY (routeId, stationId)
);


--b)
--DROP PROCEDURE add_station_to_route
GO
CREATE PROCEDURE add_station_to_route(
	@routeName VARCHAR(50),
	@stationName VARCHAR(50),
	@arrival TIME,
	@departure TIME)
AS
BEGIN
	DECLARE @nr INT, @rId INT, @sId INT;

	SELECT @rId = routeId FROM Routes WHERE routeName = @routeName
	SELECT @sId = stationId FROM Stations WHERE stationName = @stationName

	SELECT @nr = COUNT(*) FROM StationRoutes WHERE routeId = @rId AND stationId = @sId

	IF @nr = 0
	BEGIN
		INSERT INTO StationRoutes VALUES (@rId, @sId, @arrival, @departure)
	END
	ELSE
	BEGIN
		UPDATE StationRoutes
		SET arrival = @arrival, departure = @departure
		WHERE @rId = routeId AND @sId = stationId
	END
END
GO
DELETE FROM StationRoutes

add_station_to_route 'Cluj-Iasi', 'Cluj', '6:00:00', '7:00:00';
add_station_to_route 'Cluj-Iasi', 'Mures', '8:00:00', '8:10:00';
add_station_to_route 'Cluj-Iasi', 'Iasi', '10:00:00', '10:10:00';

add_station_to_route 'Cluj-Bucuresti', 'Cluj', '11:00:00', '11:30:00';
add_station_to_route 'Cluj-Bucuresti', 'Mures', '12:00:00', '12:10:00';
add_station_to_route 'Cluj-Bucuresti', 'Bucuresti', '16:00:00', '16:20:00';

add_station_to_route 'Cluj-Iasi-Bucuresti', 'Cluj', '11:00:00', '11:30:00';
add_station_to_route 'Cluj-Iasi-Bucuresti', 'Mures', '12:00:00', '12:10:00';
add_station_to_route 'Cluj-Iasi-Bucuresti', 'Iasi', '16:00:00', '16:20:00';
add_station_to_route 'Cluj-Iasi-Bucuresti', 'Bucuresti', '20:00:00', '20:30:00';

--c)

SELECT * FROM StationRoutes
ORDER BY routeId, Arrival

CREATE VIEW RoutesNames AS
	SELECT routeName
	FROM Routes R
	WHERE (SELECT COUNT (*) FROM Stations) =
		(SELECT COUNT(*) FROM StationRoutes RS WHERE R.routeId = RS.routeId)

SELECT * FROM RoutesNames


--d)
GO
CREATE FUNCTION stationsWithRRooutes (@R INT)
RETURNS TABLE
AS
RETURN 
	SELECT stationName
	FROM StationRoutes SR INNER JOIN Stations S ON SR.stationId = S.stationId
	GROUP BY S.stationName
	HAVING COUNT(*) > @R
GO

SELECT * FROM stationsWithRRooutes(3)