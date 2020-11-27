GO
CREATE VIEW RandomView
AS
SELECT RAND() AS Value
GO


--DROP FUNCTION function_random_int
GO
CREATE FUNCTION function_random_int(
	@leftBound INT,
	@rightBound INT
)
RETURNS INT
AS
BEGIN
	RETURN FLOOR((SELECT Value FROM RandomView) * (@rightBound - @leftBound) + @leftBound)
END
GO

--DROP PROCEDURE sp_insert_Authors
GO
CREATE PROCEDURE sp_insert_Authors @seed INT
AS
BEGIN
	INSERT INTO Authors(AuthorId, FirstName, LastName, DOB) VALUES
	(
		@seed, 
		'FirstName' + CONVERT(VARCHAR(10), @seed), 
		'LastName' + CONVERT(VARCHAR(10), @seed),
		'1-1-1950'
	)
END
GO

sp_insert_Authors 100

SELECT * FROM Authors
DELETE FROM Authors

--DROP PROCEDURE sp_insert_Titles
GO
CREATE PROCEDURE sp_insert_Titles @seed INT
AS
BEGIN
	INSERT INTO Titles(TitleId, Title) VALUES
	(
		@seed,
		'Title' + CONVERT(VARCHAR(10), @seed)
	)
END
GO

sp_insert_Titles 100

SELECT * FROM Titles
DELETE FROM Titles

--DROP PROCEDURE sp_insert_Authors_Titles
GO
CREATE PROCEDURE sp_insert_Authors_Titles @seed INT
AS
BEGIN
	DECLARE @author_id INT, @title_id INT, @is_generated BIT
	SET @is_generated = 0

	WHILE @is_generated = 0
	BEGIN
		SET @author_id = (SELECT TOP 1 AuthorId FROM Authors ORDER BY NEWID())
		SET @title_id = (SELECT TOP 1 TitleId FROM Titles ORDER BY NEWID())

		IF EXISTS (SELECT * FROM sys.tables WHERE name = 'InsertAuxTable')
		BEGIN
			DROP TABLE InsertAuxTable
		END

		SELECT * 
		INTO InsertAuxTable
		FROM Authors_Titles
		WHERE TitleId = @title_id

		IF EXISTS (SELECT * FROM InsertAuxTable WHERE AuthorId = @author_id)
		BEGIN
			CONTINUE
		END
		/*
		DECLARE @contribution_sum INT
		SET @contribution_sum = (SELECT SUM(ContributionPercentage) FROM AuxTable)

		IF @contribution_sum IS NULL
		BEGIN
			SET @contribution_sum = dbo.function_random_int(1, 100)
		END
		ELSE
		BEGIN
			IF @contribution_sum = 100
			BEGIN
				DROP TABLE AuxTable
				CONTINUE
			END
			--SET @contribution_sum = dbo.function_random_int(1, 100 - @contribution_sum + 1)
			SET @contribution_sum = 100 - @contribution_sum
		END
		*/
		INSERT INTO Authors_Titles(AuthorId, TitleId, ContributionPercentage) VALUES
		(
			@author_id,
			@title_id,
			100
		)

		SET @is_generated = 1
	END
END
GO

EXEC sp_populate_table 'Titles', 10;
EXEC sp_populate_table 'Authors', 10;
EXEC sp_populate_table 'Authors_Titles', 10;

SELECT * FROM Titles
SELECT * FROM Authors
SELECT * FROM Authors_Titles
ORDER BY TitleId

DELETE FROM Authors_Titles
DELETE FROM Titles
DELETE FROM Authors

--DROP PROCEDURE sp_insert_Books
GO
CREATE PROCEDURE sp_insert_Books @seed INT
AS
BEGIN
	INSERT INTO Books (BookId, LibraryId, TitleId, Pages, IBSN, PublicationYear, PublishingHouse) VALUES
	(
		@seed,
		(SELECT TOP 1 LibraryId FROM Libraries ORDER BY NEWID()),
		(SELECT TOP 1 TitleId FROM Titles ORDER BY NEWID()),
		dbo.function_random_int(30, 2000),
		CONVERT(VARCHAR(10), dbo.function_random_int(100, 1000)) + '-' +
		CONVERT(VARCHAR(10), dbo.function_random_int(100, 1000)) + '-' +
		CONVERT(VARCHAR(10), dbo.function_random_int(100, 1000)) + '-' +
		CONVERT(VARCHAR(10), dbo.function_random_int(100, 1000)) + '-' +
		CONVERT(VARCHAR(10), dbo.function_random_int(1, 10)),
		1970,
		'PublishingHouse' + CONVERT(VARCHAR(10), @seed)
	)
END
GO

sp_insert_Books 100

SELECT * FROM Books
DELETE FROM Books

--DROP PROCEDURE sp_insert_Cities
GO
CREATE PROCEDURE sp_insert_Cities @seed INT
AS
BEGIN
	INSERT INTO Cities(CityId, RegionId, CityName, CityPopulation, BorrowingPopularity)VALUES
	(
		@seed,
		(SELECT TOP 1 RegionId FROM Regions ORDER BY NEWID()),
		'CityName' + CONVERT(VARCHAR(10), @seed),
		CONVERT(VARCHAR(10), dbo.function_random_int(50000, 1000000)),
		'MEDIUM'
	)
END
GO

sp_insert_Cities 10000
SELECT * FROM Cities
DELETE FROM Cities

SELECT * FROM Cities

--DROP PROCEDURE sp_insert_Libraries
GO
CREATE PROCEDURE sp_insert_Libraries @seed INT
AS 
BEGIN
	INSERT INTO Libraries(LibraryId, CityId, LibraryAddress, LibraryName, FoundationYear) VALUES
	(
		@seed, 
		(SELECT TOP 1 CityId FROM Cities ORDER BY NEWID()),
		'LibraryAddress' + CONVERT(VARCHAR(10), @seed),
		'LibraryName' + CONVERT(VARCHAR(10), @seed),
		1970
	)
END
GO

--DROP PROCEDURE sp_populate_table
GO
CREATE PROCEDURE sp_populate_table
	@table_name VARCHAR(30),
	@number_of_rows INT
AS
BEGIN
	DECLARE @row_number INT, @command VARCHAR(512)
	SET @row_number = 1

	WHILE @row_number <= @number_of_rows
	BEGIN
		SET @command = 'sp_insert_' + @table_name + ' ' + CONVERT(VARCHAR(10), @row_number)
		EXEC(@command)
		SET @row_number = @row_number + 1
	END
END
GO

EXEC sp_populate_table 'Cities', 10000
EXEC sp_populate_table 'Libraries', 20000

SELECT * FROM HighlyPopulatedCitiesView

SELECT * FROM LibrariesAndCitiesView

SELECT * FROM NumberOfLibrariesInEachCityView
