CREATE DATABASE Lab1
GO
USE Lab1

--DROP TABLE U
CREATE TABLE U(
	id INT PRIMARY KEY,
	col1 NVARCHAR(5)
)

INSERT INTO U VALUES
(1, 'aa'), (2, 'bb')

SELECT * FROM U
DELETE FROM U WHERE id = 50
SELECT @@SERVERNAME


DROP DATABASE Ex2

DROP DATABASE Ex3
DROP DATABASE Ex4
DROP DATABASE Ex5