USE RomanianLibrariesDB

--DROP FUNCTION function_get_type
GO
CREATE FUNCTION function_get_type (@table_name VARCHAR(30), @column_name VARCHAR(30))
RETURNS VARCHAR(30)
AS 
BEGIN
DECLARE @old_type VARCHAR(30);
	
	SET @old_type = (
		SELECT DATA_TYPE
		FROM INFORMATION_SCHEMA.COLUMNS
		WHERE 
			TABLE_NAME = @table_name AND 
			COLUMN_NAME = @column_name
	);

	IF @old_type = 'varchar'
	BEGIN
		DECLARE @size INT;

		SET @size = (
			SELECT CHARACTER_MAXIMUM_LENGTH
			FROM INFORMATION_SCHEMA.COLUMNS
			WHERE 
				TABLE_NAME = @table_name AND 
				COLUMN_NAME = @column_name
		);
		SET @old_type = @old_type + '(' + CONVERT(varchar(10), @size) + ')' 
	END

	IF (SELECT IS_NULLABLE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = @table_name AND COLUMN_NAME = @column_name) = 'NO'
	BEGIN
		SET @old_type = @old_type + ' NOT NULL'
	END

	RETURN @old_type
END
GO

-- DROP PROCEDURE sp_drop_constraint
GO
CREATE PROCEDURE sp_drop_constraint
	@table_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' DROP CONSTRAINT ' + @constraint_name
	)
END
GO

-- a. modify the type of a column;

-- DROP PROCEDURE sp_modify_type
GO
CREATE PROCEDURE sp_modify_type
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@new_type VARCHAR(30)
AS
BEGIN 
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512);
	DECLARE @old_type VARCHAR(30)
	SET @old_type = dbo.function_get_type(@table_name, @column_name)

	SET @update_command = 'ALTER TABLE ' + @table_name
					   + ' ALTER COLUMN ' + @column_name + ' ' + @new_type
					   
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH
	
	SET @undo_command = 'ALTER TABLE ' + @table_name
					   + ' ALTER COLUMN ' + @column_name + ' ' + @old_type

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test sp_modify_type
-- EXEC sp_empty_history

EXEC sp_modify_type @table_name = 'TestTable', @column_name = 'secondCol', @new_type = 'VARCHAR(50)'

EXEC sp_modify_type @table_name = 'TestTable', @column_name = 'secondCol', @new_type = 'INT'


EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- b. add / remove a column;

-- DROP PROCEDURE sp_add_column
GO 
CREATE PROCEDURE sp_add_column
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@type VARCHAR(30)
AS
BEGIN 
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)
	SET @update_command = 'ALTER TABLE ' + @table_name
		+ ' ADD ' + @column_name + ' ' + @type
 
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'ALTER TABLE ' + @table_name
		+ ' DROP COLUMN ' + @column_name

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- DROP PROCEDURE sp_drop_column
GO 
CREATE PROCEDURE sp_drop_column
	@table_name VARCHAR(30),
	@column_name VARCHAR(30)
AS
BEGIN 
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'ALTER TABLE ' + @table_name
		+ ' DROP COLUMN ' + @column_name

	DECLARE @old_type VARCHAR(30)
	SET @old_type = dbo.function_get_type(@table_name, @column_name)
	
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'ALTER TABLE ' + @table_name
		+ ' ADD ' + @column_name + ' ' + @old_type

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test add/remove column
-- EXEC sp_empty_history

EXEC sp_drop_column @table_name = 'TestTable', @column_name = 'secondCol'

EXEC sp_add_column @table_name = 'TestTable', @column_name = 'secondCol', @type = 'INT'

EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- c. add / remove a DEFAULT constraint;

-- DROP PROCEDURE sp_add_default_constraint
GO
CREATE PROCEDURE sp_add_default_constraint
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30),
	@default_value VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name
		+ ' DEFAULT ' + @default_value + ' FOR ' + @column_name 
	
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH
	
	SET @undo_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- DROP PROCEDURE sp_remove_default_constraint
GO
CREATE PROCEDURE sp_remove_default_constraint
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30),
	@default_value VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name
		+ ' DEFAULT ' + @default_value + ' FOR ' + @column_name 
	
	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test add/remove default constraint
-- EXEC sp_empty_history

EXEC sp_add_default_constraint @table_name = 'TestTable', 
							   @column_name = 'col',
							   @constraint_name = 'testTable_col_default',
							   @default_value = '''test'''

EXEC sp_remove_default_constraint @table_name = 'TestTable', 
							   @column_name = 'col',
							   @constraint_name = 'testTable_col_default',
							   @default_value = '''testt'''

EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- d. add / remove a primary key;

-- DROP PROCEDURE sp_add_primary_key
GO
CREATE PROCEDURE sp_add_primary_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name + ' PRIMARY KEY(' + @column_name + ')'

	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- DROP PROCEDURE sp_remove_primary_key
GO
CREATE PROCEDURE sp_remove_primary_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'ALTER TABLE ' + @table_name
	+ ' ADD CONSTRAINT ' + @constraint_name + ' PRIMARY KEY(' + @column_name + ')'

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test add/remove primary key
-- EXEC sp_empty_history
EXEC sp_add_primary_key @table_name = 'TestTable', @column_name = 'col', @constraint_name = 'pk_col_TestTable'

EXEC sp_remove_primary_key @table_name = 'TestTable', @column_name = 'col', @constraint_name = 'pk_col_TestTable'

EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- e. add / remove a candidate key;

-- DROP PROCEDURE sp_add_candidate_key
GO 
CREATE PROCEDURE sp_add_candidate_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name + ' UNIQUE(' + @column_name + ')'
	
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	SET @undo_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- DROP PROCEDURE sp_remove_candidate_key
GO 
CREATE PROCEDURE sp_remove_candidate_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)
	
	SET @update_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH
	
	SET @undo_command = 'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name + ' UNIQUE(' + @column_name + ')'

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test add / remove candidate key
-- EXEC sp_empty_history
EXEC sp_add_candidate_key @table_name = 'TestTable', @column_name = 'anotherCol', @constraint_name = 'uk_secondCol_TestTable'

EXEC sp_remove_candidate_key @table_name = 'TestTable', @column_name = 'anotherCol', @constraint_name = 'uk_secondCol_TestTable'

EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- f. add / remove a foreign key;

-- DROP PROCEDURE sp_add_foreign_key
GO 
CREATE PROCEDURE sp_add_foreign_key
	@table_name VARCHAR(30),
	@referenced_table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@referenced_column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'ALTER TABLE ' + @table_name 
		+ ' ADD CONSTRAINT ' + @constraint_name 
		+ ' FOREIGN KEY(' + @column_name +') REFERENCES ' + @referenced_table_name + '(' + @referenced_column_name + ')' 
		
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH 

	SET @undo_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name

	EXEC sp_log_version @update_command, @undo_command
END
GO

-- DROP PROCEDURE sp_remove_foreign_key
GO 
CREATE PROCEDURE sp_remove_foreign_key
	@table_name VARCHAR(30),
	@referenced_table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@referenced_column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'sp_drop_constraint ' + @table_name + ', ' + @constraint_name
	
	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH 

	SET @undo_command = 'ALTER TABLE ' + @table_name 
		+ ' ADD CONSTRAINT ' + @constraint_name 
		+ ' FOREIGN KEY(' + @column_name +') REFERENCES ' + @referenced_table_name + '(' + @referenced_column_name + ')' 
		
	EXEC sp_log_version @update_command, @undo_command
END
GO

-- Test add / remove foreign key
-- EXEC sp_empty_history

EXEC sp_add_foreign_key @table_name = 'TestTableAnother',
						@referenced_table_name = 'TestTable',
						@column_name = 'anotherCol',
						@referenced_column_name = 'anotherCol',
						@constraint_name = 'fk_anotherCol_references_TestTable'

EXEC sp_remove_foreign_key @table_name = 'TestTableAnother',
						@referenced_table_name = 'TestTable',
						@column_name = 'anotherCol',
						@referenced_column_name = 'anotherCol',
						@constraint_name = 'fk_anotherCol_references_TestTable'

EXEC sp_bring_to_version 0

SELECT * FROM History
SELECT * FROM CurrentVersion

-- g. create / drop a table;

-- DROP PROCEDURE sp_create_table;
GO
CREATE PROCEDURE sp_create_table 
	@table_name VARCHAR(30),
	@first_column_name VARCHAR(30),
	@first_column_type VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'CREATE TABLE ' + @table_name+
		'(' + @first_column_name + ' ' + @first_column_type + ')'

	BEGIN TRY
		EXEC(@update_command)	
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH 

	SET @undo_command = 'DROP TABLE ' + @table_name
	
	EXEC sp_log_version @update_command, @undo_command
END
GO;

-- DROP PROCEDURE sp_drop_table;
GO
CREATE PROCEDURE sp_drop_table
	@table_name VARCHAR(30)
AS
BEGIN
	DECLARE @update_command VARCHAR(512), @undo_command VARCHAR(512)

	SET @update_command = 'DROP TABLE ' + @table_name
	
	IF (SELECT DuringUndoRedo FROM DuringUndoRedo) = 0
	BEGIN
		BEGIN TRY
			DECLARE ColumnCursor CURSOR FOR
				SELECT COLUMN_NAME 
				FROM INFORMATION_SCHEMA.COLUMNS
				WHERE TABLE_NAME = @table_name;
		END TRY
		BEGIN CATCH
			PRINT ERROR_MESSAGE()
			RETURN;
		END CATCH

		DECLARE @current_column VARCHAR(30), @all_columns VARCHAR(256)
		
		SET @all_columns = ''

		OPEN ColumnCursor
		FETCH ColumnCursor
		INTO @current_column

		WHILE @@FETCH_STATUS = 0
		BEGIN
			IF @all_columns = ''
			BEGIN
				SET @all_columns = @current_column + ' ' + dbo.function_get_type(@table_name, @current_column)
			END
			ELSE 
			BEGIN
				SET @all_columns = @all_columns + ', ' + @current_column + ' ' + dbo.function_get_type(@table_name, @current_column)
			END

			FETCH ColumnCursor
			INTO @current_column
		END
		CLOSE ColumnCursor
		DEALLOCATE ColumnCursor

		SET @undo_command = 'CREATE TABLE ' + @table_name + '( '
		+ @all_columns + ')'
	END

	BEGIN TRY
		EXEC(@update_command)
	END TRY
	BEGIN CATCH
		PRINT ERROR_MESSAGE()
		RETURN;
	END CATCH

	EXEC sp_log_version @update_command, @undo_command
END 
GO;

-- Test add/remove table
-- EXEC sp_empty_history

EXEC sp_create_table @table_name = 'TestAddRemoveTable', @first_column_name = 'myCol', @first_column_type = 'INT';

EXEC sp_add_column 'TestAddRemoveTable', 'mySecondCol', 'DATETIME'
EXEC sp_add_column 'TestAddRemoveTable', 'myThirdCol', 'VARCHAR(50)'

EXEC sp_drop_table @table_name = 'TestAddRemoveTable';

EXEC sp_bring_to_version 3

SELECT * FROM History
SELECT * FROM CurrentVersion

-- Create a new table that holds the current version of the database schema. Simplifying assumption: the version is an integer number.

-- Write a stored procedure that receives as a parameter a version number and brings the database to that version.


-- table which holds the current version(has only one row and one column)
-- DROP TABLE CurrentVersion
CREATE TABLE CurrentVersion(
	CurrentVersion INT NOT NULL DEFAULT 0
);
INSERT INTO CurrentVersion (CurrentVersion) VALUES (0)

SELECT CurrentVersion FROM CurrentVersion

-- table which holds a bit value named DuringUndo(has only one row and one column)
	-- if it's 1 logging can't be done in the History table
	-- if it's 0 otherwise
-- DROP TABLE DuringUndoRedo
CREATE TABLE DuringUndoRedo(
	DuringUndoRedo BIT NOT NULL DEFAULT 0
);

INSERT INTO DuringUndoRedo (DuringUndoRedo) VALUES (0)

SELECT * FROM DuringUndoRedo

-- table which holds the history of all made changes
-- consists of:
--		a version number (the version after the update was made)
--		update command string (string of the command)
--		undo command string (string that reverts the update command
--		always contains at least one row which describes the version 0 (the base version) with update and undo command as empty strings

-- DROP TABLE History
CREATE TABLE History(
	Version int PRIMARY KEY,
	UpdateCommand VARCHAR(512),
	UndoCommand VARCHAR(512)
);
INSERT INTO History (Version, UpdateCommand, UndoCommand) VALUES (0, '', '')

SELECT * FROM History

-- DROP PROCEDURE sp_log_version
GO
CREATE PROCEDURE sp_log_version
	@update_command VARCHAR(512),
	@undo_command VARCHAR(512)
AS
BEGIN
	IF (SELECT DuringUndoRedo FROM DuringUndoRedo) = 1
	BEGIN
		RETURN;
	END

	DECLARE @current_version INT;
	DECLARE @latest_version INT;

	SET @current_version = (SELECT CurrentVersion FROM CurrentVersion);
	SET @latest_version = (SELECT MAX(Version) FROM History);

	IF @current_version != @latest_version
	BEGIN 
		DELETE FROM History
		WHERE Version > @current_version;
	END;
	INSERT INTO History VALUES(@current_version + 1, @update_command, @undo_command);

	UPDATE CurrentVersion
	SET CurrentVersion = @current_version + 1
END
GO

-- DROP sp_empty_history
GO
CREATE PROCEDURE sp_empty_history
AS
BEGIN
	DELETE FROM History
	WHERE Version != 0;

	UPDATE CurrentVersion
	SET CurrentVersion = 0
END 
GO

-- EXEC sp_empty_history


-- DROP PROCEDURE sp_downgrade_version
GO
CREATE PROCEDURE sp_downgrade_version
AS
BEGIN
	DECLARE @current_version INT;
	SET @current_version = (SELECT CurrentVersion FROM CurrentVersion);
	
	IF @current_version != 0
	BEGIN
		DECLARE @undoCommand VARCHAR(512);
		SET @undoCommand = (SELECT UndoCommand FROM History WHERE Version = @current_version);

		EXEC(@undoCommand);

		UPDATE CurrentVersion
		SET CurrentVersion = @current_version - 1
	END
END
GO

-- DROP PROCEDURE sp_upgrade_version
GO
CREATE PROCEDURE sp_upgrade_version
AS
BEGIN
	DECLARE @current_version INT;
	SET @current_version = (SELECT CurrentVersion FROM CurrentVersion);
	
	IF @current_version != (SELECT MAX(Version) FROM History)
	BEGIN
		DECLARE @updateCommand VARCHAR(512);
		SET @updateCommand = (SELECT UpdateCommand FROM History WHERE Version = @current_version + 1);

		EXEC(@updateCommand);

		UPDATE CurrentVersion
		SET CurrentVersion = @current_version + 1
	END
END
GO

-- DROP PROCEDURE sp_bring_to_version
GO
CREATE PROCEDURE sp_bring_to_version
	@version INT
AS 
BEGIN
	DECLARE @latest_version INT;
	DECLARE @current_version INT;
	SET @latest_version = (SELECT MAX(Version) FROM History);
	SET @current_version = (SELECT CurrentVersion FROM CurrentVersion)

	IF @version < 0 OR @version > @latest_version
	BEGIN
		PRINT('Version must be at least 0 (earliest version) and at most: ' + CONVERT(VARCHAR(10), @latest_version) + ' (latest version)')
		RETURN;
	END
	
	IF @version = @current_version
	BEGIN
		PRINT('Already at the required version')
		RETURN;
	END

	UPDATE DuringUndoRedo
	SET DuringUndoRedo = 1
	
	WHILE @version < (SELECT CurrentVersion FROM CurrentVersion)
	BEGIN 
			EXEC sp_downgrade_version
	END

	WHILE @version > (SELECT CurrentVersion FROM CurrentVersion)
	BEGIN 
			EXEC sp_upgrade_version
	END

	UPDATE DuringUndoRedo
	SET DuringUndoRedo = 0
END
GO

EXEC sp_bring_to_version 0

EXEC sp_log_version 'PRINT(''update1'')', 'PRINT(''undo1'')'
EXEC sp_log_version 'PRINT(''update2'')', 'PRINT(''undo2'')'
EXEC sp_log_version 'PRINT(''update3'')', 'PRINT(''undo3'')'

SELECT * FROM History
SELECT * FROM CurrentVersion

--Final tests

EXEC sp_create_table 'FinalTestTable', 'firstCol', 'INT';
EXEC sp_create_table 'FinalSecondTestTable', 'secondCol', 'VARCHAR(30)';

EXEC sp_add_column 'FinalTestTable', 'secondCol', 'INT NOT NULL'

EXEC sp_modify_type 'FinalSecondTestTable', 'secondCol', 'INT NOT NULL'

EXEC sp_add_default_constraint 'FinalTestTable', 'firstCol', 'firstCol_defaults_to_0', '0'

EXEC sp_add_primary_key 'FinalTestTable', 'secondCol', 'pk_second_col'

EXEC sp_add_candidate_key 'FinalTestTable', 'firstCol', 'uk_firstCol'

EXEC sp_add_foreign_key 'FinalSecondTestTable', 'FinalTestTable', 'secondCol', 'secondCol', 'fk_secondCol_to_FinalTestTable'

EXEC sp_remove_candidate_key 'FinalTestTable', 'firstCol', 'uk_firstCol'

EXEC sp_remove_default_constraint 'FinalTestTable', 'firstCol', 'firstCol_defaults_to_0', '0'

EXEC sp_drop_column 'FinalTestTable', 'firstCol'

EXEC sp_remove_foreign_key 'FinalSecondTestTable', 'FinalTestTable', 'secondCol', 'secondCol', 'fk_secondCol_to_FinalTestTable'

EXEC sp_remove_primary_key 'FinalTestTable', 'secondCol', 'pk_second_col'

EXEC sp_add_column 'FinalTestTable', 'testCol', 'INT'

EXEC sp_drop_table 'FinalTestTable'

EXEC sp_bring_to_version 4


SELECT * FROM History 
SELECT * FROM CurrentVersion

-- EXEC sp_empty_history
