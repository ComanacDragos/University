USE Libraries
GO

GO
SELECT @@TRANCOUNT

-- create a stored procedure that inserts data in tables that are in a m:n relationship; 
-- if one insert fails, all the operations performed by the procedure must be rolled back 

GO 
--DROP PROCEDURE sp_validate_title
CREATE PROCEDURE sp_validate_title 
	@title VARCHAR(100)
AS 
BEGIN
	IF @title = ''
	BEGIN
		RAISERROR (15600,-1,-1, 'First name must not be empty.'); 
	END
END
GO
--DROP PROCEDURE sp_validate_author 
GO
CREATE PROCEDURE sp_validate_author 
	@firstName VARCHAR(50),
	@lastName VARCHAR(50),
	@DOB DATE
AS 
BEGIN
	IF @firstName = ''
	BEGIN
		RAISERROR (15600,-1,-1, 'First name must not be empty.'); 
	END

	IF @lastName = ''
	BEGIN
		RAISERROR (15600,-1,-1, 'Last name must not be empty.'); 
	END

	IF @DOB > (SELECT CURRENT_TIMESTAMP AS current_date_time)
	BEGIN
		RAISERROR (15600,-1,-1, 'DOB must not be in the future'); 
	END
END
GO

sp_validate_author '', 'asd', '12-12-2020';
GO
sp_validate_author 'asd', '', '12-12-2020';
GO
sp_validate_author 'asd', 'asd', '12-12-2024'

-- DROP PROCEDURE sp_insert_author_title
GO
CREATE PROCEDURE sp_insert_author_title 
	@title VARCHAR(100),
	@contributionPercentage INT,
	@firstName VARCHAR(50),
	@lastName VARCHAR(50),
	@DOB date
AS 
BEGIN
	DECLARE @authorId INT, @titleId INT;

	SELECT @authorId = MaxAuthorId
	FROM (
		SELECT MAX(AuthorId) as MaxAuthorId
		FROM Authors
	) t
	IF @authorId is NULL
	BEGIN
		SET @authorId = 0
	END
	SET @authorId = @authorId + 1

	SELECT @titleId = MaxTitleId
	FROM (
		SELECT MAX(TitleId) as MaxTitleId
		FROM Titles
	) t
	IF @titleId is NULL
	BEGIN
		SET @titleId = 0
	END
	SET @titleId = @titleId + 1

	DECLARE @newData VARCHAR(100)
	DECLARE @auxTable TABLE(
		currentTime DATETIME,
		info VARCHAR(100), 
		oldData VARCHAR(100), 
		newData VARCHAR(100),
		error VARCHAR(1000)
	)

	BEGIN TRAN
	BEGIN TRY
		EXEC sp_validate_author @firstName, @lastName, @DOB 
		INSERT INTO Authors (AuthorId, FirstName, LastName, DOB) VALUES
		(@authorId, @firstName, @lastName, @DOB)
		PRINT 'INSERTED AUTHOR'
		SET @newData = @firstName + ' ' + @lastName
		INSERT INTO @auxTable (currentTime, newData, info) VALUES
			(GETDATE(), @newData, 'INSERTED AUTHOR')
		
		EXEC sp_validate_title @title
		INSERT INTO Titles (TitleId, Title) VALUES
		(@titleId, @title)
		PRINT 'INSERTED TITLE'
		INSERT INTO @auxTable (currentTime, newData, info) VALUES
			(GETDATE(), @title, 'INSERTED TITLE')
		
		INSERT INTO Authors_Titles (AuthorId, TitleId, ContributionPercentage) VALUES
		(@authorId, @titleId, @contributionPercentage)
		PRINT 'INSERTED AUTHOR_TITLE'
		SET @newData = CAST(@authorId as varchar(10)) + ' - ' + CAST(@titleId as varchar(10)) + ' - ' + CAST(@contributionPercentage as varchar(10)) 
		INSERT INTO @auxTable (currentTime, newData, info) VALUES
			(GETDATE(), @newData, 'INSERTED TITLE')

		PRINT 'SUCCESS!'
		COMMIT TRAN
	END TRY
	BEGIN CATCH
		DECLARE @error VARCHAR(1000)
		 SELECT @error = ERROR_MESSAGE()
		PRINT 'Error: ' + @error
		EXEC sp_log_changes @oldData = '', @newData = '', @info = '', @error = @error
		INSERT INTO @auxTable(currentTime, error) VALUES
			(GETDATE(), @error)
		ROLLBACK
	END CATCH

	INSERT INTO ChangesLog
		SELECT * FROM @auxTable
END
GO

SELECT * FROM Authors
ORDER BY AuthorId
SELECT * FROM Titles
ORDER BY TitleId
SELECT * FROM Authors_Titles

SELECT * FROM ChangesLog
ORDER BY currentTime

EXEC sp_insert_author_title @title = 'newTitle', @contributionPercentage = 30, @firstName = 'firstName', @lastName = 'lastName', @DOB ='12-12-1990'

EXEC sp_insert_author_title @title = 'newTitle1', @contributionPercentage = -30, @firstName = 'firstName1', @lastName = 'lastName1', @DOB ='12-12-1990'

EXEC sp_insert_author_title @title = 'newTitle', @contributionPercentage = -30, @firstName = 'firstName1', @lastName = 'lastName1', @DOB ='12-12-3000'

EXEC sp_insert_author_title @title = '', @contributionPercentage = -30, @firstName = 'firstName1', @lastName = 'lastName1', @DOB ='12-12-3000'

DELETE FROM Authors_Titles
DELETE FROM Authors
DELETE FROM Titles

--create a stored procedure that inserts data in tables that are in a m:n relationship; 
--if an insert fails, try to recover as much as possible from the entire operation: 
--for example, if the user wants to add a book and its authors, succeeds creating the authors, 
-- but fails with the book, the authors should remain in the database 

--DROP PROCEDURE sp_insert_authors_title
GO
CREATE PROCEDURE sp_insert_authors_title 
	@title VARCHAR(100),
	@contributionPercentage1 INT,
	@firstName1 VARCHAR(50),
	@lastName1 VARCHAR(50),
	@DOB1 date,
	@contributionPercentage2 INT,
	@firstName2 VARCHAR(50),
	@lastName2 VARCHAR(50),
	@DOB2 date
AS 
BEGIN
	DECLARE @authorId1 INT, @authorId2 INT, @titleId INT;
	DECLARE @error VARCHAR(1000);

	SELECT @authorId1 = MaxAuthorId
	FROM (
		SELECT MAX(AuthorId) as MaxAuthorId
		FROM Authors
	) t
	IF @authorId1 is NULL
	BEGIN
		SET @authorId1 = 0
	END
	SET @authorId1 = @authorId1 + 1
	SET @authorId2 = @authorId1 + 1

	SELECT @titleId = MaxTitleId
	FROM (
		SELECT MAX(TitleId) as MaxTitleId
		FROM Titles
	) t
	IF @titleId is NULL
	BEGIN
		SET @titleId = 0
	END
	SET @titleId = @titleId + 1

	DECLARE @newData VARCHAR(1000)

	BEGIN TRY
		EXEC sp_validate_author @firstName1, @lastName1, @DOB1 
		INSERT INTO Authors (AuthorId, FirstName, LastName, DOB) VALUES
		(@authorId1, @firstName1, @lastName1, @DOB1)
		PRINT 'INSERTED AUTHOR1'
		SET @newData = @firstName1 + ' ' + @lastName1
		EXEC sp_log_changes @oldData = NULL, @newData = @newData, @info = 'INSERTED AUTHOR1', @error = NULL
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		PRINT 'Error on inserting AUTHOR1: ' + @error
		EXEC sp_log_changes @oldData = NULL, @newData = NULL, @info = 'Error on inserting AUTHOR1', @error = @error
	END CATCH

	BEGIN TRY
		EXEC sp_validate_author @firstName2, @lastName2, @DOB2 
		INSERT INTO Authors (AuthorId, FirstName, LastName, DOB) VALUES
		(@authorId2, @firstName2, @lastName2, @DOB2)
		PRINT 'INSERTED AUTHOR2'
		SET @newData = @firstName2 + ' ' + @lastName2
		EXEC sp_log_changes @oldData = NULL, @newData = @newData, @info = 'INSERTED AUTHOR2', @error = NULL
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		PRINT 'Error on inserting AUTHOR2: ' + @error
		EXEC sp_log_changes @oldData = NULL, @newData = NULL, @info = 'Error on inserting AUTHOR2', @error = @error
	END CATCH

	BEGIN TRY
		EXEC sp_validate_title @title
		INSERT INTO Titles (TitleId, Title) VALUES
		(@titleId, @title)
		PRINT 'INSERTED TITLE'
		EXEC sp_log_changes @oldData = NULL, @newData = @title, @info = 'INSERTED TITLE', @error = NULL
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		PRINT 'Error on inserting TITLE: ' + @error
		EXEC sp_log_changes @oldData = NULL, @newData = NULL, @info = 'Error on inserting TITLE', @error = @error
	END CATCH

	BEGIN TRY 
		INSERT INTO Authors_Titles (AuthorId, TitleId, ContributionPercentage) VALUES
		(@authorId1, @titleId, @contributionPercentage1)
		PRINT 'INSERTED AUTHOR_TITLE1'
		SET @newData = CAST(@authorId1 as VARCHAR(10)) + ' - ' + CAST(@titleId as VARCHAR(10)) + ' - ' + CAST(@contributionPercentage1 as VARCHAR(10))
		EXEC sp_log_changes @oldData = NULL, @newData = @newData, @info = 'INSERTED AUTHOR_TITLE1', @error = NULL
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		PRINT 'Error on inserting AUTHOR_TITLE1: ' + @error
		EXEC sp_log_changes @oldData = NULL, @newData = NULL, @info = 'Error on inserting AUTHOR_TITLE1', @error = @error
	END CATCH

	BEGIN TRY 
		INSERT INTO Authors_Titles (AuthorId, TitleId, ContributionPercentage) VALUES
		(@authorId2, @titleId, @contributionPercentage2)
		PRINT 'INSERTED AUTHOR_TITLE2'
		SET @newData = CAST(@authorId2 as VARCHAR(10)) + ' - ' + CAST(@titleId as VARCHAR(10)) + ' - ' + CAST(@contributionPercentage2 as VARCHAR(10))
		EXEC sp_log_changes @oldData = NULL, @newData = @newData, @info = 'INSERTED AUTHOR_TITLE2', @error = NULL
	END TRY
	BEGIN CATCH
		SELECT @error = ERROR_MESSAGE()
		PRINT 'Error on inserting AUTHOR_TITLE2: ' + @error
		EXEC sp_log_changes @oldData = NULL, @newData = NULL, @info = 'Error on inserting AUTHOR_TITLE2', @error = @error
	END CATCH
END
GO

SELECT * FROM Authors
ORDER BY AuthorId
SELECT * FROM Titles
ORDER BY TitleId
SELECT * FROM Authors_Titles


SELECT * FROM ChangesLog
ORDER BY currentTime

EXEC sp_insert_authors_title @title = 'newTitle', 
							 @contributionPercentage1 = 50, @firstName1 = 'firstName1', @lastName1 = 'lastName1', @DOB1 ='11-11-1991',
							 @contributionPercentage2 = 50, @firstName2 = 'firstName2', @lastName2 = 'lastName2', @DOB2 ='12-12-1992'
		
EXEC sp_insert_authors_title @title = '', 
							 @contributionPercentage1 = 50, @firstName1 = 'firstName1', @lastName1 = 'lastName1', @DOB1 ='11-11-1991',
							 @contributionPercentage2 = 50, @firstName2 = 'firstName2', @lastName2 = 'lastName2', @DOB2 ='12-12-1992'
				
						
EXEC sp_insert_authors_title @title = 'title', 
							 @contributionPercentage1 = 50, @firstName1 = 'firstName1', @lastName1 = 'lastName1', @DOB1 ='11-11-2991',
							 @contributionPercentage2 = 50, @firstName2 = 'firstName2', @lastName2 = 'lastName2', @DOB2 ='12-12-1992'
			
DELETE FROM Authors_Titles
DELETE FROM Authors
DELETE FROM Titles
