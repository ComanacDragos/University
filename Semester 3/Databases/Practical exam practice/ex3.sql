--CREATE DATABASE Ex3
GO
USE Ex3
GO

DROP TABLE ProductionActors
DROP TABLE Productions
DROP TABLE Movies
DROP TABLE StageDirectors
DROP TABLE Companies
DROP TABLE Actors

GO

CREATE TABLE Actors(
	actorId INT PRIMARY KEY,
	name VARCHAR(100),
	ranking INT
)

CREATE TABLE Companies(
	companyId INT PRIMARY KEY,
	name VARCHAR(100),
)

CREATE TABLE Directors(
	directorId INT PRIMARY KEY,
	name VARCHAR(100),
	awards INT
)

CREATE TABLE Movies(
	movieId INT PRIMARY KEY,
	name VARCHAR(100),
	releaseDate DATE,
	companyId INT FOREIGN KEY REFERENCES Companies(companyId),
	directorId INT FOREIGN KEY REFERENCES Directors(directorId)
)

CREATE TABLE Productions(
	productionId INT PRIMARY KEY,
	name VARCHAR(100),
	movieId INT FOREIGN KEY REFERENCES Movies(movieId)
)

CREATE TABLE ProductionActors(
	actorId INT FOREIGN KEY REFERENCES Actors(actorId),
	productionId INT FOREIGN KEY REFERENCES Productions(productionId),
	entryMoment VARCHAR(100),
	CONSTRAINT pk_prod_actors PRIMARY KEY (actorId, productionId)
)

GO

INSERT INTO Actors (actorId, name)VALUES
(1,'n1'),
(2,'n2'),
(3,'n3')

INSERT INTO Directors(directorId, name)VALUES
(1,'d1'),
(2,'d2'),
(3,'d3')

INSERT INTO Companies(companyId, name)VALUES
(1,'c1'),
(2,'c2'),
(3,'c3')

INSERT INTO Movies(movieId, name, releaseDate, companyId, directorId)VALUES
(1,'m1', '1-1-2017', 1, 1),
(2,'m2', '2-2-2018', 2,2),
(3,'m3', '3-3-2019', 3,3)

INSERT INTO Productions(productionId, name, movieId)VALUES
(1,'p1', 1),
(2,'p2', 1),
(3,'p3', 1),
(4,'p4', 2),
(5,'p5', 2),
(6,'p6', 3)

GO
CREATE OR ALTER PROC add_actor_prod(@actor VARCHAR(100), @production VARCHAR(100), @moment VARCHAR(100))
AS
	IF NOT EXISTS (SELECT * FROM Actors WHERE name = @actor)
	BEGIN
		RAISERROR('Actor does not exist', 16,1)
		RETURN
	END

	IF NOT EXISTS (SELECT * FROM Productions WHERE name = @production)
	BEGIN
		RAISERROR('Production does not exist', 16,1)
		RETURN
	END

	INSERT INTO ProductionActors(actorId, productionId,entryMoment)VALUES
	(
		(SELECT actorId FROM Actors WHERE name = @actor),
		(SELECT productionId FROM Productions WHERE name = @production),
		@moment
	)
GO

EXEC add_actor_prod 'nd1','p1', 'moment1'
GO
EXEC add_actor_prod 'n1','p1g', 'moment1'
GO

EXEC add_actor_prod 'n1','p1', 'moment1'
EXEC add_actor_prod 'n1','p2', 'moment1'
EXEC add_actor_prod 'n1','p3', 'moment1'
EXEC add_actor_prod 'n1','p4', 'moment1'
EXEC add_actor_prod 'n1','p5', 'moment1'
EXEC add_actor_prod 'n1','p6', 'moment1'

EXEC add_actor_prod 'n2','p1', 'moment1'
EXEC add_actor_prod 'n2','p2', 'moment1'
EXEC add_actor_prod 'n2','p3', 'moment1'
EXEC add_actor_prod 'n2','p4', 'moment1'
EXEC add_actor_prod 'n2','p5', 'moment1'
EXEC add_actor_prod 'n2','p6', 'moment1'

EXEC add_actor_prod 'n3','p1', 'moment1'


GO
CREATE VIEW popular_actors
AS
SELECT name
FROM Actors
WHERE actorId IN (
		SELECT actorId
		FROM ProductionActors
		GROUP BY actorId
		HAVING COUNT(*) = (SELECT COUNT(*) FROM Productions)
	)
GO
SELECT * FROM popular_actors

GO
CREATE FUNCTION popular_movies(@P INT)
RETURNS TABLE
AS	
RETURN 
	SELECT M.name
	FROM Movies M INNER JOIN Productions P ON M.movieId = P.movieId
	WHERE releaseDate >= '2018-1-1'
	GROUP BY M.movieId, M.name
	HAVING COUNT(*) >= @P
GO

SELECT * FROM popular_movies(1)
SELECT * FROM popular_movies(2)
SELECT * FROM popular_movies(3)