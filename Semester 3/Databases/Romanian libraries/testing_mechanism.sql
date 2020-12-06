-- DROP PROCEDURE sp_create_test
GO
CREATE PROCEDURE sp_create_test
	@test_name VARCHAR(50)
AS
BEGIN
	IF @test_name IN (SELECT Name FROM Tests)
	BEGIN
		PRINT 'There exists a test with this name'
		RETURN
	END
	INSERT INTO Tests (Name) VALUES(@test_name)
END
GO

EXEC sp_create_test 'test1'

SELECT * FROM Tests

-- Insert into Tables the tables which we want to test

-- DROP PROCEDURE sp_add_table_to_be_tested
GO
CREATE PROCEDURE sp_add_table_to_be_tested
	@table_name VARCHAR(50)
AS
BEGIN 
	IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.TABLES  WHERE TABLE_NAME = @table_name)
	BEGIN
		IF @table_name NOT IN (SELECT Name FROM Tables)
		BEGIN
			INSERT INTO Tables (Name) VALUES (@table_name)
		END
		ELSE 
		BEGIN 
			PRINT('Table already added')
		END
	END
	ELSE
	BEGIN
		PRINT('Table ' + @table_name + ' does not exist')
	END
END
GO

EXEC sp_add_table_to_be_tested 'Titles'
EXEC sp_add_table_to_be_tested 'Authors'
EXEC sp_add_table_to_be_tested 'Authors_Titles'
EXEC sp_add_table_to_be_tested 'Books'

SELECT * FROM Tables

--DROP PROCEDURE sp_connect_table_to_test
GO
CREATE PROCEDURE sp_connect_table_to_test
	@table_name VARCHAR(50),
	@test_name VARCHAR(50),
	@number_of_rows INT,
	@position INT
AS 
BEGIN 
	IF @position <= 0
	BEGIN 
		PRINT 'Position must be greater than 0'
		RETURN
	END

	IF @number_of_rows <= 0
	BEGIN 
		PRINT 'Number of rows must be greater than 0'
		RETURN
	END

	DECLARE @test_id INT, @table_id INT

	SET @test_id = (SELECT TestID FROM Tests WHERE Name = @test_name)
	IF @test_id IS NULL
	BEGIN
		PRINT 'There is no test with that name'
		RETURN
	END
	
	SET @table_id = (SELECT TableID FROM Tables WHERE Name = @table_name)
	IF @table_id IS NULL
	BEGIN
		PRINT 'There is no table with that name'
		RETURN
	END
	BEGIN TRY
		INSERT INTO TestTables(TestID, TableID, NoOfRows, Position) VALUES
		(@test_id, @table_id, @number_of_rows, @position)
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

SELECT *
FROM Tables

EXEC sp_connect_table_to_test 'Authors', 'test1', 200, 1

SELECT * FROM TestTables
DELETE FROM TestTables

-- Insert into Views the views which we want to test

-- DROP PROCEDURE sp_add_view_to_be_tested
GO
CREATE PROCEDURE sp_add_view_to_be_tested
	@view_name VARCHAR(50)
AS
BEGIN 
	IF EXISTS (SELECT * FROM INFORMATION_SCHEMA.VIEWS  WHERE TABLE_NAME = @view_name)
	BEGIN
		IF @view_name NOT IN (SELECT Name FROM Views)
		BEGIN
			INSERT INTO Views (Name) VALUES (@view_name)
		END
		ELSE 
		BEGIN 
			PRINT('View already added')
		END
	END
	ELSE
	BEGIN
		PRINT('View ' + @view_name + ' does not exist')
	END
END
GO

EXEC sp_add_view_to_be_tested 'HighlyPopulatedCitiesView'
EXEC sp_add_view_to_be_tested 'LibrariesAndCitiesView'
EXEC sp_add_view_to_be_tested 'NumberOfLibrariesInEachCityView'

SELECT * FROM Views

SELECT * FROM Tables

--DROP PROCEDURE sp_connect_view_to_test
GO
CREATE PROCEDURE sp_connect_view_to_test
	@view_name VARCHAR(50),
	@test_name VARCHAR(50)
AS 
BEGIN 
	DECLARE @test_id INT, @view_id INT

	SET @test_id = (SELECT TestID FROM Tests WHERE Name = @test_name)
	IF @test_id IS NULL
	BEGIN
		PRINT 'There is no test with that name'
		RETURN
	END
	
	SET @view_id = (SELECT ViewID FROM Views WHERE Name = @view_name)
	IF @view_id IS NULL
	BEGIN
		PRINT 'There is no view with that name'
		RETURN
	END
	BEGIN TRY
		INSERT INTO TestViews(TestID, ViewID) VALUES
		(@test_id, @view_id)
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
	END CATCH
END
GO

--DROP PROCEDURE sp_run_test
GO
CREATE PROCEDURE sp_run_test @test_name VARCHAR(50)
AS
BEGIN
	DECLARE @test_id INT
	SET @test_id = (SELECT TestID FROM Tests WHERE Name = @test_name)

	IF @test_id IS NULL
	BEGIN 
		PRINT 'There is not test with that name'
		RETURN
	END

	DECLARE TablesCursor CURSOR SCROLL FOR
		SELECT Tables.TableID, Tables.Name, TestTables.NoOfRows
		FROM TestTables INNER JOIN Tables ON TestTables.TableID = Tables.TableID
		WHERE TestTables.TestID = @test_id
		ORDER BY TestTables.Position
	
	DECLARE ViewsCursor CURSOR FOR
		SELECT V.ViewID, V.Name
		FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID
		WHERE TV.TestID = @test_id

	DECLARE @table VARCHAR(50),
	@number_of_rows INT,
	@position INT,
	@table_id INT,
	@global_start_time DATETIME2,
	@global_end_time DATETIME2,
	@local_start_time DATETIME2,
	@local_end_time DATETIME2,
	@view_id INT,
	@view VARCHAR(50),
	@test_run_id INT,
	@command VARCHAR(512)

	SET NOCOUNT ON

	INSERT INTO TestRuns(Description) VALUES
	('Test results for: ' + @test_name)

	SET @test_run_id = CONVERT(INT, (SELECT last_value FROM sys.identity_columns WHERE name = 'TestRunID'))

	SET @global_start_time = SYSDATETIME()
	OPEN TablesCursor
	FETCH FIRST FROM TablesCursor
	INTO @table_id, @table, @number_of_rows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		EXEC('DELETE FROM ' + @table)
		
		FETCH NEXT FROM TablesCursor
		INTO @table_id, @table, @number_of_rows	
	END

	CLOSE TablesCursor
	OPEN TablesCursor

	FETCH LAST FROM TablesCursor
	INTO @table_id, @table, @number_of_rows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @command = 'sp_populate_table ''' + @table + ''', ' + CONVERT(VARCHAR(10), @number_of_rows)
		
		SET @local_start_time = SYSDATETIME()
		EXEC(@command)
		SET @local_end_time = SYSDATETIME()
		INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt) VALUES
		(@test_run_id, @table_id, @local_start_time, @local_end_time)
		
		FETCH PRIOR FROM TablesCursor
		INTO @table_id, @table, @number_of_rows
	END
	
	OPEN ViewsCursor
	FETCH ViewsCursor
	INTO @view_id, @view
	
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @command = 'SELECT * FROM ' + @view
		
		SET @local_start_time = SYSDATETIME()
		EXEC(@command)
		SET @local_end_time = SYSDATETIME()

		INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt) VALUES
		(@test_run_id, @view_id, @local_start_time, @local_end_time)
		
		FETCH ViewsCursor
		INTO @view_id, @view
	END
	SET @global_end_time = SYSDATETIME()

	UPDATE TestRuns
	SET StartAt = @global_start_time, EndAt = @global_end_time
	WHERE TestRunID = @test_run_id

	CLOSE TablesCursor
	CLOSE ViewsCursor
	DEALLOCATE ViewsCursor
	DEALLOCATE TablesCursor

	SET NOCOUNT OFF
END
GO

--DROP PROCEDURE sp_results_for_test
GO
CREATE PROCEDURE sp_results_for_test @test_name VARCHAR(50)
AS 
BEGIN
	SELECT * FROM TestRuns
	WHERE Description LIKE '%' + @test_name + '%'

	SELECT TT.TestRunID, T.Name, TT.StartAt, TT.EndAt 
	FROM TestRunTables TT INNER JOIN Tables T ON TT.TableID = T.TableID
	WHERE TT.TestRunID IN (
		SELECT TestRunID FROM TestRuns
		WHERE Description LIKE '%' + @test_name + '%'
	)
	ORDER BY StartAt
	
	SELECT TV.TestRunID, V.Name, TV.StartAt, TV.EndAt
	FROM TestRunViews TV INNER JOIN VIEWS V ON TV.ViewID = V.ViewID
	WHERE TV.TestRunID IN (
		SELECT TestRunID FROM TestRuns
		WHERE Description LIKE '%' + @test_name + '%'
	)
	ORDER BY StartAt
END
GO
-- setup test1

EXEC sp_connect_view_to_test 'HighlyPopulatedCitiesView', 'test1'
EXEC sp_connect_view_to_test 'LibrariesAndCitiesView', 'test1'
EXEC sp_connect_view_to_test 'NumberOfLibrariesInEachCityView', 'test1'

SELECT * FROM TestViews
SELECT * FROM Views

EXEC sp_connect_table_to_test 'Books', 'test1', 5000, 1
EXEC sp_connect_table_to_test 'Authors_Titles', 'test1', 5000, 2
EXEC sp_connect_table_to_test 'Authors', 'test1', 2000, 3
EXEC sp_connect_table_to_test 'Titles', 'test1', 2000, 4


SELECT * FROM TestTables
SELECT * FROM Tables

SELECT * FROM Tests




SELECT * FROM Authors_Titles
SELECT * FROM Authors
SELECT * FROM Titles
SELECT * FROM Books

EXEC sp_run_test 'test1'


DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews



-- setup test2
EXEC sp_create_test 'test2'

EXEC sp_connect_table_to_test 'Books', 'test2', 1000, 1
EXEC sp_connect_table_to_test 'Authors_Titles', 'test2', 1000, 2
EXEC sp_connect_table_to_test 'Authors', 'test2', 500, 3
EXEC sp_connect_table_to_test 'Titles', 'test2', 500, 4

EXEC sp_connect_view_to_test 'NumberOfLibrariesInEachCityView', 'test2'

EXEC sp_run_test 'test2'

EXEC sp_results_for_test 'test2'
