--!!!Please don't execute the file!!!--
--Execute only up until the puzzle--

DECLARE @command VARCHAR(555), @number_of_columns INT
SET @command = 'CREATE TABLE MyTable(id int'
SET @number_of_columns = 17

WHILE @number_of_columns != -1
BEGIN
	SET @command = @command + ',c' + CONVERT(VARCHAR(10), @number_of_columns) + ' VARCHAR(3)'
	SET @number_of_columns = @number_of_columns - 1
END

SET @command = @command + ')'

EXEC(@command) -- creates a table with @number_of_columns columns

-- Bonus query:
-- One way to create a new table with the structure of an existing table is using TOP 0
SELECT TOP 0 * INTO AuxTable FROM MyTable

SELECT * FROM MyTable

SELECT * FROM AuxTable

-- Bonus to bonus query
INSERT INTO MyTable 
(id,  c0 ,  c1 ,  c2 ,  c8 ,  c3 ,  c5 ,  c7 ,  c9 , c10 , c12 , c11 , c13 , c15 , c14 , c17 )
VALUES
(2 ,'|  ','   ',' | ','   ','|  ','  |','|  ','   ','___','   ',')  ','|  ','___','   ','  )'),
(4 ,'\__','___','___','___','___','/  ','|  ','___','___','___','/  ','|  ','___','___','  /'),
(1 ,' __','___','_  ','   ',' __','_  ',' __','___','___','___','   ',' __','___','___','   '),
(3 ,'|  ','   ',' | ','   ','|  ','  |','|  ','   ','___','   ','\  ','|  ','___','   ','  \')

--PUZZLE--
SELECT * -- Primes and multiples of 5 matter
FROM MyTable
--Order matters x2


--SCROLL FOR SOLUTION--
























































SELECT c0, c2, c3, c5, c7, c10, c11, c13, c15, c17
FROM MyTable
ORDER BY id