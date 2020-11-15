-- DROP TABLE MyTable
CREATE TABLE MyTable(
	id int,
	c1 VARCHAR(3),
	c2 VARCHAR(3),
	c3 VARCHAR(3),
	c4 VARCHAR(3),
	c5 VARCHAR(3),
	c6 VARCHAR(3),
	c7 VARCHAR(3),
	c8 VARCHAR(3),
	c9 VARCHAR(3),
	c10 VARCHAR(3),
	c11 VARCHAR(3),
	c12 VARCHAR(3),
	c13 VARCHAR(3),
	c14 VARCHAR(3),
	c15 VARCHAR(3)
)

-- Bonus query:
-- One way to create a new table with the structure of an existing table
SELECT TOP 0 * INTO AuxTable FROM MyTable

SELECT * FROM MyTable

SELECT * FROM AuxTable


-- Bonus to bonus query
DELETE FROM MyTable
INSERT INTO MyTable 
(id,  c1 ,  c2 ,  c3 ,  c4 ,  c5 ,  c6 ,  c7 ,  c8 ,  c9 , c10 , c11 , c12 , c13 , c14 , c15 )
VALUES
(2 ,'|  ','   ',' | ','   ','|  ','  |','|  ','   ','___','   ',')  ','|  ','___','   ','  )'),
(4 ,'\__','___','___','___','___','/  ','|  ','___','___','___','/  ','|  ','___','___','  /'),
(1 ,' __','___','_  ','   ',' __','_  ',' __','___','___','___','   ',' __','___','___','   '),
(3 ,'|  ','   ',' | ','   ','|  ','  |','|  ','   ','___','   ','\  ','|  ','___','   ','  \')




