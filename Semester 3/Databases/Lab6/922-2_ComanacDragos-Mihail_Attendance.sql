USE RomanianLibrariesDB

-- a. modify the type of a column;
-- b. add / remove a column;
-- c. add / remove a DEFAULT constraint;
-- d. add / remove a primary key;
-- e. add / remove a candidate key;
-- f. add / remove a foreign key;
-- g. create / drop a table;

-- DROP PROCEDURE create_table;
GO
CREATE PROCEDURE create_table 
	@table_name varchar(30),
	@first_column_name varchar(30),
	@first_column_type varchar(30)
AS
BEGIN
	IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(@table_name))
		RETURN
	DECLARE @SQLString NVARCHAR(MAX)
    SET @SQLString = 'CREATE TABLE ' + @table_name+
    '(
     ' + @first_column_name + ' ' + @first_column_type + ')'
	EXEC (@SQLString)
	
END
GO;

-- DROP PROCEDURE drop_table;

CREATE PROCEDURE drop_table
	@table_name varchar(30)
AS
BEGIN
	IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(@table_name))
		DECLARE @SQLString NVARCHAR(MAX)
		SET @SQLString = 'DROP TABLE ' + @table_name
		EXEC (@SQLString)
	
END 
GO;

EXEC create_table @table_name = 'TestTable1', @first_column_name = 'col', @first_column_type = 'INT';

EXEC drop_table @table_name = 'TestTable1';
