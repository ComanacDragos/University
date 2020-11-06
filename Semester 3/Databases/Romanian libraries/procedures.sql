USE RomanianLibrariesDB

-- a. modify the type of a column;

-- DROP PROCEDURE sp_modify_type
GO
CREATE PROCEDURE sp_modify_type
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@new_type VARCHAR(30)
AS
BEGIN 
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' ALTER COLUMN ' + @column_name + ' ' + @new_type
		)
END
GO

EXEC sp_modify_type @table_name = 'TestTable', @column_name = 'col', @new_type = 'VARCHAR(30) NOT NULL'


-- b. add / remove a column;

-- DROP PROCEDURE sp_add_column
GO 
CREATE PROCEDURE sp_add_column
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@type VARCHAR(30)
AS
BEGIN 
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' ADD ' + @column_name + ' ' + @type
		)
END
GO

-- DROP PROCEDURE sp_drop_column
GO 
CREATE PROCEDURE sp_drop_column
	@table_name VARCHAR(30),
	@column_name VARCHAR(30)
AS
BEGIN 
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' DROP COLUMN ' + @column_name
		)
END
GO

EXEC sp_add_column @table_name = 'TestTable', @column_name = 'secondCol', @type = 'INT'
EXEC sp_add_column @table_name = 'TestTable', @column_name = 'anotherCol', @type = 'INT'

EXEC sp_drop_column @table_name = 'TestTable', @column_name = 'secondCol'

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
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name
		+ ' DEFAULT ' + @default_value + ' FOR ' + @column_name
	)
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

EXEC sp_add_default_constraint @table_name = 'TestTable', 
							   @column_name = 'col',
							   @constraint_name = 'testTable_col_default',
							   @default_value = '''test'''

EXEC sp_drop_constraint @table_name = 'TestTable', @constraint_name = 'testTable_col_default'

-- d. add / remove a primary key;

-- DROP PROCEDURE sp_add_primary_key
GO
CREATE PROCEDURE sp_add_primary_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name + ' PRIMARY KEY(' + @column_name + ')'
	)
END
GO

EXEC sp_add_primary_key @table_name = 'TestTable', @column_name = 'col', @constraint_name = 'pk_col_TestTable'

EXEC sp_drop_constraint @table_name = 'TestTable', @constraint_name = 'pk_col_TestTable'

-- e. add / remove a candidate key;

-- DROP PROCEDURE sp_add_candidate_key
GO 
CREATE PROCEDURE sp_add_candidate_key
	@table_name VARCHAR(30),
	@column_name VARCHAR(30),
	@constraint_name VARCHAR(30)
AS
BEGIN
	EXEC(
		'ALTER TABLE ' + @table_name
		+ ' ADD CONSTRAINT ' + @constraint_name + ' UNIQUE(' + @column_name + ')'
	)
END
GO

EXEC sp_add_candidate_key @table_name = 'TestTable', @column_name = 'anotherCol', @constraint_name = 'uk_secondCol_TestTable'

EXEC sp_drop_constraint @table_name = 'TestTable', @constraint_name = 'uk_secondCol_TestTable'

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
	EXEC(
		'ALTER TABLE ' + @table_name 
		+ ' ADD CONSTRAINT ' + @constraint_name 
		+ ' FOREIGN KEY(' + @column_name +') REFERENCES ' + @referenced_table_name + '(' + @referenced_column_name + ')' 
	)
END
GO

EXEC sp_add_foreign_key @table_name = 'TestTableAnother',
						@referenced_table_name = 'TestTable',
						@column_name = 'anotherCol',
						@referenced_column_name = 'anotherCol',
						@constraint_name = 'fk_anotherCol_references_TestTable'

EXEC sp_drop_constraint @table_name = 'TestTableAnother', @constraint_name = 'fk_anotherCol_references_TestTable'

-- g. create / drop a table;

-- DROP PROCEDURE sp_create_table;
GO
CREATE PROCEDURE sp_create_table 
	@table_name VARCHAR(30),
	@first_column_name VARCHAR(30),
	@first_column_type VARCHAR(30)
AS
BEGIN
	EXEC(
		'CREATE TABLE ' + @table_name+
		'(
		 ' + @first_column_name + ' ' + @first_column_type 
		 + ')'
	)
END
GO;

-- DROP PROCEDURE sp_drop_table;
GO
CREATE PROCEDURE sp_drop_table
	@table_name VARCHAR(30)
AS
BEGIN
	EXEC(
		'DROP TABLE ' + @table_name
	)
END 
GO;

EXEC sp_create_table @table_name = 'TestTableAnother', @first_column_name = 'anotherCol', @first_column_type = 'INT';

EXEC sp_drop_table @table_name = 'AnotherTestTable';

-- Create a new table that holds the current version of the database schema. Simplifying assumption: the version is an integer number.

-- Write a stored procedure that receives as a parameter a version number and brings the database to that version.