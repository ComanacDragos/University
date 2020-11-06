USE RomanianLibrariesDB

/*
You must use:

- arithmetic expressions(d,g,i) in the SELECT clause in at least 3 queries;
- conditions with AND, OR, NOT, and parentheses(d) in the WHERE clause in at least 3 queries;
- DISTINCT in at least 3 queries, ORDER BY in at least 2 queries, and TOP(e) in at least 2 queries.
*/

-- a. 2 queries with the union operation; use UNION [ALL] and OR;

-- Get all persons in the database which are born after 2000 or before 1900

SELECT FirstName + ' ' + LastName AS 'Full Name', DateOfBirth
FROM Borrowers 
WHERE DateOfBirth >= '1-1-2000' OR DateOfBirth < '1-1-1900'
UNION
SELECT FirstName + ' ' + LastName AS 'Full Name', DOB AS 'DateOfBirth'
FROM Authors
WHERE DOB >= '1-1-2000' OR DOB < '1-1-1900'

-- Get all titles which contain biography or philosophy ordered by title 

SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Biography' OR T2.TopicName = 'Philosophy'
ORDER BY T3.Title

/*
SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Biography'
UNION
SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Philosophy'
ORDER BY T3.Title
*/

-- b. 2 queries with the intersection operation; use INTERSECT and IN;

-- Fiind all titles which contain biography and philosophy

SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Biography' 
INTERSECT
SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Philosophy' 

-- Find all the distinct titles which are both in 'Biblioteca Centrala Universitara Lucian Blaga' and in 'Biblioteca Judeteana Mihai Eminescu' ordered descending by title

SELECT T.Title
FROM Books B 
INNER JOIN Titles T ON T.TitleID = B.TitleId
INNER JOIN Libraries L ON B.LibraryId = L.LibraryId
WHERE L.LibraryName = 'Biblioteca Centrala Universitara Lucian Blaga' AND T.Title IN
(
	SELECT T.Title
	FROM Books B 
	INNER JOIN Titles T ON T.TitleID = B.TitleId
	INNER JOIN Libraries L ON B.LibraryId = L.LibraryId
	WHERE L.LibraryName = 'Biblioteca Judeteana Mihai Eminescu'
)
ORDER BY T.Title DESC

/*
SELECT T.Title
FROM Books B INNER JOIN Titles T ON T.TitleID = B.TitleId
WHERE B.LibraryId =
(SELECT LibraryId
FROM Libraries
WHERE LibraryName = 'Biblioteca Judeteana Mihai Eminescu'
) 
INTERSECT 
SELECT DISTINCT T.Title
FROM Books B INNER JOIN Titles T ON T.TitleID = B.TitleId
WHERE B.LibraryId =
(SELECT LibraryId
FROM Libraries
WHERE LibraryName = 'Biblioteca Centrala Universitara Lucian Blaga'
) 
ORDER BY T.Title DESC
*/


-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;

-- Fiind all titles which contain biography but not philosophy

SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Biography' 
EXCEPT
SELECT DISTINCT T3.Title
FROM Topics_Titles T1
INNER JOIN Topics T2 ON T1.TopicId = T2.TopicId
INNER JOIN Titles T3 ON T1.TitleId = T3.TitleId
WHERE T2.TopicName = 'Philosophy' 

-- Find all the distinct titles which are not in Transilvania ordered descending by title

SELECT Title
FROM Titles
WHERE TitleId NOT IN (
	SELECT DISTINCT T.TitleId
	FROM Libraries L 
	INNER JOIN Books B ON L.LibraryId = B.LibraryId
	INNER JOIN Titles T ON T.TitleId = B.TitleId
	INNER JOIN Cities C ON L.CityId = C.CityId
	INNER JOIN Regions R ON C.RegionId = R.RegionId
	WHERE R.Name = 'Transilvania' 
)
ORDER BY Title DESC


-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator);
-- one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

-- Get the topics and topics percentage of the books "Un veac de singuratate" or "Amintiri din copilarie" ordered by title then by topic percentage, having the topic percentage at least 40%

SELECT T2.Title, T1.TopicName, TT.TopicPercentage
FROM Topics_Titles TT
INNER JOIN Topics T1 ON TT.TopicId = T1.TopicId
INNER JOIN Titles T2 ON TT.TitleId = T2.TitleId
WHERE (T2.Title = 'Un veac de Singuratate' OR T2.Title = 'Amintiri din copilarie') AND TT.TopicPercentage >= 40
ORDER BY T2.Title, TT.TopicPercentage DESC

-- For all libraries, get the publishing houses of their books (including the libraries which do not have books)

SELECT DISTINCT L.LibraryName, B.PublishingHouse
FROM Books B
RIGHT JOIN Libraries L ON B.LibraryId = L.LibraryId
ORDER BY L.LibraryName

-- Get the topics used by each author, including those topics that are not used by any authors

SELECT DISTINCT A.FirstName + ' ' + A.LastName AS 'Full Name', T.TopicName
FROM Topics T
LEFT JOIN Topics_Titles TT ON TT.TopicId = T.TopicId
LEFT JOIN Authors_Titles AT ON AT.TitleId = TT.TitleId
LEFT JOIN Authors A ON A.AuthorId = AT.AuthorId
ORDER BY [Full name] DESC, T.TopicName

-- Get all borrowers  and the books they borrowed. Also show all borrowers which did not borrow any books and all books which are not borrowed

SELECT B1.FirstName + ' ' + B1.LastName AS 'Full Name', B2.Title
FROM Borrowers_Books BB 
FULL OUTER JOIN Borrowers B1 ON B1.BorrowerId = BB. BorrowerId
FULL OUTER JOIN (
	SELECT B.BookId, T.Title 
	FROM Books B INNER JOIN Titles T ON B.TitleId = T.TitleId
) B2 ON BB.BookId = B2.BookId

-- e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery should include a subquery in its own WHERE clause;

-- Get the top 50 percent libraries in Transilvania with the most books

SELECT TOP 50 PERCENT L.LibraryName
FROM Libraries L INNER JOIN Books B ON L.LibraryId = B.LibraryId
WHERE L.CityId IN(
	SELECT C.CityId
	FROM Cities C INNER JOIN Regions R ON C.RegionId = R.RegionId
	WHERE R.Name = 'Transilvania'
)
GROUP BY L.LibraryName
ORDER BY COUNT(L.LibraryName) DESC

-- Get the characters from the top 3 most borrowed books toghether with the title in which they appear in

SELECT C.FullName, T.Title
FROM Characters C INNER JOIN Titles T ON C.TitleId = T.TitleId
WHERE T.Title IN (
	SELECT T1.Title
	FROM Titles T1 INNER JOIN Books B1 ON T1.TitleId = B1.TitleId
	WHERE B1.BookId IN(
		SELECT TOP 3 B2.BookId
		FROM Books B2
		INNER JOIN Borrowers_Books BB ON B2.BookId = BB.BookId
		INNER JOIN Borrowers B3 ON BB.BorrowerId = B3.BorrowerId
		GROUP BY B2.BookId
		ORDER BY COUNT(B2.BookId) DESC
	)
)
ORDER BY T.Title

-- f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;

-- Get all authors which wrote the book "Structuri de date si algoritmi" ordered by their last name

SELECT A.FirstName + ' ' + A.LastName AS 'Full Name'
FROM Authors A
WHERE EXISTS(
	SELECT *
	FROM Authors_Titles AT INNER JOIN Titles T ON AT.TitleId = T.TitleId
	WHERE A.AuthorId = AT.AuthorId AND T.Title = 'Structuri de date si algoritmi'
)
ORDER BY A.LastName

-- Get all titles which contain biography ordered by title

SELECT T1.Title
FROM Titles T1
WHERE EXISTS(
	SELECT *
	FROM Topics_Titles TT INNER JOIN Topics T2 ON TT.TopicId = T2.TopicId
	WHERE TT.TitleId = T1.TitleId AND T2.TopicName = 'Biography'
)
ORDER BY T1.Title

-- g. 2 queries with a subquery in the FROM clause;         

-- Get all the topics of the books from 'Biblioteca Centrala Universitara Lucian Blaga' having at least 400 pages

SELECT DISTINCT T1.TopicName, TL.Title
FROM  Topics_Titles TT 
INNER JOIN Topics T1 ON TT.TopicId = T1.TopicId
INNER JOIN (
	SELECT L.LibraryName, T2.Title, T2.TitleId
	FROM Titles T2
	INNER JOIN Books B ON T2.TitleId = B.TitleId
	INNER JOIN Libraries L ON B.LibraryId = L.LibraryId
	WHERE B.Pages >= 400
) TL ON TT.TitleId = TL.TitleId -- books with more than 400 pages and their libraries
WHERE TL.LibraryName = 'Biblioteca Centrala Universitara Lucian Blaga'
ORDER BY TL.Title

-- Show the borrowers cities and the books they have borrowed together with the cities and the libraries in which they are in and the start and end date of the borrowing and the number of weeks borrowed as a float

SELECT BC.FullName, BC.CityName 'As borrower city', BTC.Title, BTC.CityName AS 'Book city',BTC.LibraryName AS 'Book library',
FORMAT(BB.StartDate, 'dd-MM-yyyy') AS 'Start Date', FORMAT(BB.EndDate, 'dd-MM-yyyy') AS 'End Date', FORMAT(DATEDIFF(DAY,BB.StartDate, BB.EndDate)/7.0, 'N2') AS 'Number of weeks borrowed'
FROM Borrowers_Books BB
INNER JOIN (
	SELECT B1.BookId, T.Title, C.CityName, L.LibraryName
	FROM Books B1 
	INNER JOIN Titles T ON B1.TitleId = T.TitleId
	INNER JOIN Libraries L ON B1.LibraryId = L.LibraryId
	INNER JOIN Cities C ON L.CityId = C.CityId
) AS BTC ON BTC.BookId = BB.BookId  -- book data
INNER JOIN (
	SELECT B2.BorrowerId, B2.FirstName + ' ' + B2.LastName AS 'FullName', C1.CityName
	FROM Borrowers B2 INNER JOIN Cities C1 ON B2.CityId = C1.CityId
) BC ON BB.BorrowerId = BC.BorrowerId -- borrower data
ORDER BY BC.FullName

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause;
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- Get the number of books per each topic that has at least one book ordered descending

SELECT T1.TopicName, COUNT(T1.TopicName) AS 'Number of books'
FROM Topics T1
INNER JOIN (
	SELECT TT.TopicId
	FROM Books B 
	INNER JOIN Titles T2 ON B.TitleId = T2.TitleId
	INNER JOIN Topics_Titles TT ON TT.TitleId = T2.TitleId
) TB ON T1.TopicId = TB.TopicId
GROUP BY T1.TopicName
ORDER BY COUNT(T1.TopicName) DESC, T1.TopicName

-- Get the libraries from Moldova which have exactly 2 books borrowed

SELECT L.LibraryName
FROM Libraries L INNER JOIN Books B ON L.LibraryId = B.LibraryId
WHERE L.CityId IN(
	SELECT C.CityId
	FROM Cities C INNER JOIN Regions R ON C.RegionId = R.RegionId
	WHERE R.Name = 'Moldova'
)
GROUP BY L.LibraryName
HAVING COUNT(L.LibraryName) = 2

-- Get the authors which have written more books than Paulo Coelho

SELECT A.FirstName + ' ' + A.LastName AS 'FullName', COUNT(T.Title) AS 'WrittenBooks'
FROM Authors A
INNER JOIN Authors_Titles AT ON A.AuthorId = AT.AuthorId
INNER JOIN Titles T ON T.TitleId = AT.TitleId
GROUP BY A.FirstName + ' ' + A.LastName
HAVING COUNT(T.Title) > (
	SELECT COUNT(T.Title)
	FROM Authors A
	INNER JOIN Authors_Titles AT ON A.AuthorId = AT.AuthorId
	INNER JOIN Titles T ON T.TitleId = AT.TitleId
	WHERE A.FirstName = 'Paulo' AND A.LastName = 'Coelho'	
	GROUP BY A.FirstName + ' ' + A.LastName
)
ORDER BY A.FirstName + ' ' + A.LastName

-- Get the cities in witch the oldest book from the city is older than the average of the region
-- Transilvania avg: 1980, Moldova avg: 1968, Tara Romaneasca avg: 1967

SELECT BC.CityName, MIN(BC.PublicationYear) AS 'Earliest year'
FROM (
	SELECT T.Title, C.CityName, B.PublicationYear, C.RegionId
	FROM Books B
	INNER JOIN Titles T ON B.TitleId = T.TitleId
	INNER JOIN Libraries L ON B.LibraryId = L.LibraryId
	INNER JOIN Cities C ON C.CityId = L.CityId
) BC
GROUP BY BC.CityName, BC.RegionId
HAVING MIN(BC.PublicationYear) < (
	SELECT AVG(B.PublicationYear)
	FROM Books B
	INNER JOIN Titles T ON B.TitleId = T.TitleId
	INNER JOIN Libraries L ON B.LibraryId = L.LibraryId
	INNER JOIN Cities C ON C.CityId = L.CityId
	WHERE C.RegionId = BC.RegionId
)
ORDER BY BC.RegionId

 
-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator);
-- rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.

-- Get all books which have been borrowed before all books with the title 'Jurnalul unui mag'

SELECT DISTINCT T.Title
FROM Borrowers_Books BB 
INNER JOIN Books B ON BB.BookId = B.BookId
INNER JOIN Titles T ON B.TitleId = T.TitleId
WHERE BB.StartDate < ALL (
	SELECT BB.StartDate
	FROM Borrowers_Books BB 
	INNER JOIN Books B ON BB.BookId = B.BookId
	INNER JOIN Titles T ON B.TitleId = T.TitleId
	WHERE T.Title = 'Jurnalul unui mag'
)

SELECT DISTINCT T.Title
FROM Borrowers_Books BB 
INNER JOIN Books B ON BB.BookId = B.BookId
INNER JOIN Titles T ON B.TitleId = T.TitleId
WHERE BB.StartDate <(
	SELECT MIN(BB.StartDate)
	FROM Borrowers_Books BB 
	INNER JOIN Books B ON BB.BookId = B.BookId
	INNER JOIN Titles T ON B.TitleId = T.TitleId
	WHERE T.Title = 'Jurnalul unui mag'
)


-- Get the books together with the publishing house which have more pages than Nunta in cer from any publishing house

SELECT DISTINCT T.Title, B.PublishingHouse, B.Pages
FROM Books B 
INNER JOIN Titles T ON B.TitleId = T.TitleId 
WHERE B.Pages > ALL(
	SELECT B1.Pages
	FROM Books B1 
	INNER JOIN Titles T1 ON B1.TitleId = T1.TitleId 
	WHERE T1.Title = 'Nunta in cer'
)

SELECT DISTINCT T.Title, B.PublishingHouse, B.Pages
FROM Books B 
INNER JOIN Titles T ON B.TitleId = T.TitleId
WHERE B.Pages > (
	SELECT MAX(B1.Pages)
	FROM Books B1 
	INNER JOIN Titles T1 ON B1.TitleId = T1.TitleId 
	WHERE T1.Title = 'Nunta in cer'
)

--get the titles which share the topics of 'Noaptea de sanziene'(also write the percentage as the TopicPercentage/100)

SELECT T1.Title, T2.TopicName, FORMAT(TT.TopicPercentage/100.0,'N2')
FROM Titles T1 
INNER JOIN Topics_Titles TT ON T1.TitleId = TT.TitleId
INNER JOIN Topics T2 ON TT.TopicId = T2.TopicId
WHERE T2.TopicName = ANY(
	SELECT T2.TopicName
	FROM Titles T1 
	INNER JOIN Topics_Titles TT ON T1.TitleId = TT.TitleId
	INNER JOIN Topics T2 ON TT.TopicId = T2.TopicId
	WHERE T1.Title = 'Noaptea de Sanziene'
)
ORDER BY T1.Title
		
SELECT T1.Title, T2.TopicName, FORMAT(TT.TopicPercentage/100.0,'N2')
FROM Titles T1 
INNER JOIN Topics_Titles TT ON T1.TitleId = TT.TitleId
INNER JOIN Topics T2 ON TT.TopicId = T2.TopicId
WHERE T2.TopicName IN (
	SELECT T2.TopicName
	FROM Titles T1 
	INNER JOIN Topics_Titles TT ON T1.TitleId = TT.TitleId
	INNER JOIN Topics T2 ON TT.TopicId = T2.TopicId
	WHERE T1.Title = 'Noaptea de Sanziene'
)
ORDER BY T1.Title

-- Get the authors which did write about philosophy

SELECT A.FirstName + ' ' + A.LastName AS 'Full Name'
FROM Authors A 
WHERE A.AuthorId = ANY(
	SELECT DISTINCT AT1.AuthorId
	FROM Authors_Titles AT1 
	INNER JOIN Topics_Titles TT ON AT1.TitleId = TT.TitleId
	INNER JOIN Topics T2 ON T2.TopicId = TT.TopicId
	WHERE T2.TopicName = 'Philosophy'
)
ORDER BY [Full Name]

SELECT A.FirstName + ' ' + A.LastName AS 'Full Name'
FROM Authors A 
WHERE A.AuthorId IN(
	SELECT DISTINCT AT1.AuthorId
	FROM Authors_Titles AT1 
	INNER JOIN Topics_Titles TT ON AT1.TitleId = TT.TitleId
	INNER JOIN Topics T2 ON T2.TopicId = TT.TopicId
	WHERE T2.TopicName = 'Philosophy'
)
ORDER BY [Full Name]

