USE RomanianLibrariesDB

-- a. 2 queries with the union operation; use UNION [ALL] and OR;

-- Get all persons in the database

SELECT FirstName + ' ' + LastName AS 'Full Name'
FROM Borrowers 
UNION
SELECT FirstName + ' ' + LastName AS 'Full Name'
FROM Authors

-- Get all titles which contain biography or philosophy ordered by title

SELECT DISTINCT T1.Title
FROM Titles T1, Topics T2, Topics_Titles T3
WHERE T1.TitleId = T3.TitleId AND T2.TopicId = T3.TopicId 
AND (T2.TopicName = 'Biography' OR T2.TopicName = 'Philosophy')
ORDER BY T1.Title


-- b. 2 queries with the intersection operation; use INTERSECT and IN;

-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;

-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator);
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- Get the topics and topics percentage of the book "Un veac de singuratate" ordered by topic percentage

SELECT T2.Title, T1.TopicName, TT.TopicPercentage
FROM Topics_Titles TT
INNER JOIN Topics T1 ON TT.TopicId = T1.TopicId
INNER JOIN Titles T2 ON TT.TitleId = T2.TitleId
WHERE T2.Title = 'Un veac de Singuratate'
ORDER BY TT.TopicPercentage DESC

-- For all libraries, get the publishing houses of their books (including the libraries which do not have books)

SELECT DISTINCT L.LibraryName, B.PublishingHouse
FROM Books B
RIGHT JOIN Libraries L ON B.LibraryId = L.LibraryId
ORDER BY L.LibraryName

-- Get the topics used by each author, including those topics that are not used by any authors

SELECT T1.TopicName, T2.Title
FROM Topics T1
LEFT JOIN Topics_Titles TT ON TT.TopicId = T1.TopicId
LEFT JOIN Titles T2 ON T2.TitleId = TT.TitleId
--to be continued

-- e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause;

-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

-- g. 2 queries with a subquery in the FROM clause;                                        

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause;
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator);
-- rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.