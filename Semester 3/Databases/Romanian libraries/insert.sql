USE RomanianLibrariesDB

INSERT INTO Regions(RegionId, Name) VALUES
(1, 'Transilvania'),
(2, 'Moldova'),
(3, 'Tara Romaneasca');	

SELECT * FROM Regions

INSERT INTO Cities(CityId, RegionId, CityName, CityPopulation) VALUES
(1, 1, 'Cluj-Napoca', 706905),
(2, 1, 'Sibiu', 401000),
(3, 1, 'Timisoara', 306000),
(4, 2, 'Botosani', 107000),
(5, 2, 'Piatra-Neamt', 104000),
(6, 2, 'Suceava', 106500),
(7, 2, 'Iasi', 700000),
(8, 3, 'Bucuresti', 2419400),
(9, 3, 'Constanta', 673000);

SELECT * FROM Cities

INSERT INTO Topics(TopicId, TopicName) VALUES
(1, 'Drama'),
(2, 'Science Fiction'),
(3, 'Romance'),
(4, 'Survival'),
(5, 'Power and corruption'),
(6, 'Family'),
(7, 'Rural'),
(8, 'Urban'),
(9, 'Biography'),
(10, 'History'),
(11, 'War'),
(12, 'Fiction'),
(13, 'Action'),
(14, 'Adventure'),
(15, 'Comic'),
(16, 'Classic'),
(17, 'Mystery'),
(18, 'Fantasy'),
(19, 'Horror'),
(20, 'Thriller'),
(21, 'Cookbook'),
(22, 'Philosophy'),
(23, 'Scientific'); 

SELECT * FROM Topics;

INSERT INTO Libraries(LibraryId, CityId, LibraryAddress, LibraryName, FoundationYear) VALUES
(1, 1, 'Str. Clinicilor 2', 'Biblioteca Centrala Universitara Lucian Blaga', 1872),
(2, 1, 'Str. Calea Dorobantilor 104', 'Biblioteca Judeteana Octavian Goga', 1921),
(3, 2, 'Str. George Baritiu', 'Biblioteca Judeteana Astra', 1963),
(4, 2, 'Str. Lucian Blaga 2A', 'Biblioteca Centrala a Universitatii', 1969),
(5, 3, 'Piata Libertatii nr. 3', 'Biblioteca Judeteana Timis', 1904),
(6, 4, 'Calea Nationala 62', 'Biblioteca Judeteana Mihai Eminescu', 1882),
(7, 5, 'Bulevardul Republicii 15A', 'Biblioteca Judeteana G.T. Kirileanu', 1869),
(8, 6, 'Bulevardul Stefan Cel Mare', 'Biblioteca I.G. SBIERA', 1923),
(9, 7, 'Str. Pacurari nr 4', 'Biblioteca Centrala Universitara Mihai Eminescu', 1835),
(10, 8, 'Bulevardul Unirii 22', 'Biblioteca Nationala a Romaniei', 1859),
(11, 9, 'Str. Mircea cel Batran 104A', 'Bibliteca Judeteana Ioan N. Roman', 1931);

INSERT INTO Libraries(LibraryId, CityId, LibraryAddress, LibraryName, FoundationYear) VALUES
(12, 1, 'Str. Teodor Mihali 58-60', 'Biblioteca FSEGA', 2000),
(13, 8, 'Str. Bibliotecii 5', 'Biblioteca Bucuresti', 1990),
(14, 9, 'Str. Primaverii 10', 'Biblioteca Constanta', 1995);

SELECT * FROM Libraries

--DELETE FROM BOOKS

INSERT INTO Titles(TitleId, Title) VALUES
(1, 'Un veac de Singuratate'),
(2, 'Noaptea de Sanziene'),
(3, 'Jurnalul unui mag'),
(4, 'Amintiri din copilarie'),
(5, 'Nunta in cer'),
(6, 'Silogismele Amaraciunii'),
(7, 'Tratat de descompunere'),
(8, 'Romanul adolescentului miop'),
(9, 'Fratii Jderi'),
(10, 'Din Calidor'),
(11, 'Maitreyi'),
(12, 'Structuri de date si algoritmi'),
(13, 'Istoria orasului Botosani');

SELECT * FROM Titles

INSERT INTO Books(BookId, LibraryId, TitleId, Pages, IBSN, PublicationYear, PublishingHouse) VALUES
(1, 1, 1, 480, '978-973-103-462-1', 1967, 'Rao'),
(2, 1, 2, 645, NULL, 1955, 'Editions Gallimard'),
(3, 2, 3, 200, '543-785-123-876-2', 1987, 'Humanitas'),
(4, 3, 4, 50, NULL, 1892, 'Humanitas'),
(5, 3, 1, 500, '978-973-103-462-1', 1990, 'Humanitas'),
(6, 4, 5, 200, '959-200-443-123-4', 1995, 'Adevarul'),
(7, 5, 6, 100, NULL, 1984, 'Humanitas'),
(8, 5, 2, 685, NULL, 1955, 'Albatros'),
(9, 6, 7, 200, '298-263-696-223-1', 1949, 'Humanitas'),
(10, 6, 1, 529, '178-373-463-462-1', 1967, 'Humanitas'),
(11, 7, 8, 300, '423-875-195-023-2', 1989, 'Minerva'),
(12, 7, 4, 50, NULL, 1970, 'Albatros'),
(13, 8, 9, 1000, '843-678-232-123-1', 1892, 'Minerva'),
(14, 9, 10, 100, NULL, 1987, 'Albatros'),
(15, 9, 5, 230, '312-230-343-223-4', 1995, 'Adevarul'),
(16, 10, 2, 645, NULL, 1955, 'Editions Gallimard'),
(17, 10, 3, 200, '443-385-223-576-7', 1987, 'Humanitas'),
(18, 10, 4, 50, NULL, 1892, 'Humanitas'),
(19, 10, 1, 500, '148-173-103-462-1', 1967, 'Humanitas'),
(20, 11, 11, 100, '234-432-654-753-0', 1933, 'Humanitas'),
(21, 2, 12, 500, NULL, 2000, 'Universitatea'),
(22, 6, 13, 50, '123-432-123-413-5', 1995, 'Adevarul');

SELECT * FROM Books
ORDER BY TitleId

--DELETE FROM AUTHORS

INSERT INTO Authors(AuthorId, FirstName, LastName, DOB) VALUES
(1, 'Gabriel Garcia', 'Marquez', '03-06-1927'),
(2, 'Mircea', 'Eliade', '03-13-1907'),
(3, 'Emil', 'Cioran', '04-08-1911'),
(4, 'Paulo', 'Coelho', '08-24-1947'),
(5, 'Ion', 'Creanga', '03-01-1837'),
(6, 'Mihail', 'Sadoveanu', '11-05-1880'),
(7, 'Ion', 'Popescu', '4-3-1950'),
(8, 'Mihai', 'Popescu', '12-3-1949'),
(9, 'Andrei', 'Andreescu', '5-5-1970'),
(10, 'Cristian', 'Ionescu', '9-23-1965'),
(11, 'Ion', 'Ionescu', '10-23-1977');

INSERT INTO Authors(AuthorId, FirstName, LastName, DOB) VALUES
(12, 'Matei', 'Florin', '1-1-2001');

INSERT INTO Authors(AuthorId, FirstName, LastName, DOB) VALUES
(13, 'Paul', 'Goma', '10-2-1935');

SELECT * FROM Authors 

INSERT INTO Borrowers(BorrowerId, CityId, FirstName, LastName, DateOfBirth, Gender) VALUES
(1, 4, 'Mihai', 'Andrei', '1-1-1997', 'M'),
(2, 1, 'Liviu', 'Andreescu', '9-03-2005', 'M'),
(3, 5, 'Laura', 'Neamtu', '07-31-2000', 'F'),
(4, 8, 'Andrei', 'Gheorgiu', '6-30-2001', 'M'),
(5, 7, 'Elena', 'Neamtu', '7-31-2000', 'F'),
(6, 3, 'Marius', 'Gheorghescu', '3-3-1995', 'M'),
(7, 2, 'John', 'Smith', '2-29-1992', 'M');

SELECT * FROM Borrowers

INSERT INTO Characters(CharacterId, TitleId, FullName, CharacterRole) VALUES
(1, 1, 'Jose Arcadio Buendia', 'Primary'),
(2, 1, 'Pilar Ternera', 'Secondary'),
(3, 2, 'Stefan Viziru', 'Primary'),
(4, 2, 'Ioana Viziru', 'Secondary'),
(5, 3, 'Calauza', 'Primary'),
(6, 4, 'Nica', 'Primary'),
(7, 5, 'Andrei Mavrodin', 'Primary'),
(8, 5, 'Barbu Hasnas', 'Primary'),
(9, 9, 'Ionut', 'Primary'),
(10, 11, 'Maitreyi', 'Primary'),
(11, 8, 'Naratorul', 'Primary');

SELECT * FROM Characters

INSERT INTO Authors_Titles(AuthorId, TitleId, ContributionPercentage) VALUES
(1, 1, 100),
(2, 2, 100),
(2, 8, 100),
(2, 11, 100),
(2, 5, 100),
(3, 6, 100),
(3, 7, 100),
(4, 3, 100),
(5, 4, 100),
(6, 9, 100),
(7, 12, 60),
(10, 12, 40),
(8, 13, 10),
(9, 13, 25),
(10, 13, 20),
(11, 13, 45);

INSERT INTO Authors_Titles(AuthorId, TitleId, ContributionPercentage) VALUES
(13, 10, 100);

SELECT T.Title, A.FirstName + ' ' + A.LastName
FROM Authors A, Authors_Titles A_T, Titles T
WHERE A.AuthorId = A_T.AuthorId AND T.TitleId = A_T.TitleId

--DELETE FROM Topics_TItles

INSERT INTO Topics_Titles (TopicId, TitleId, TopicPercentage) VALUES
(6, 1, 60),
(1, 1, 20),
(11, 1, 20),
(3, 2, 30),
(9, 2, 40),
(22, 2, 30),
(22, 3, 20),
(9, 3, 80),
(6, 4, 40),
(9, 4, 60),
(3, 5, 100),
(22, 6, 100),
(22, 7,  100),
(3, 8, 20),
(8, 8, 10),
(15, 8, 20),
(9, 8, 50),
(11, 9, 20),
(10, 9 ,70),
(12, 9, 10),
(6, 10, 50),
(9, 10, 50),
(9, 11, 20),
(3, 11, 80),
(23, 12, 100),
(10, 13, 50),
(23, 13, 50);

SELECT T1.Title, T2. TopicName, T3.TopicPercentage
FROM Titles T1, Topics T2, Topics_Titles T3
WHERE T1.TitleId = T3.TitleId AND T2.TopicId = T3.TopicId
ORDER BY T1.Title

-- DELETE FROM Borrowers_Books

INSERT INTO Borrowers_Books(BorrowerBookId, BookId, BorrowerId, StartDate, EndDate)VALUES
(1, 1, 1, '4-1-2019', '4-4-2019'),
(2, 1, 1, '1-1-2020', '1-20-2020'),
(3, 10, 3, '5-5-2020', NULL),
(4, 17, 6, '7-6-2020', '7-10-2020'),
(5, 21, 7, '10-10-2020', NULL),
(6, 6, 1,'2-4-2019', '10-04-2019'),
(7, 13, 5, '11-9-2020', NULL),
(8, 15, 7, '3-3-2020', NULL);

INSERT INTO Borrowers_Books(BorrowerBookId, BookId, BorrowerId, StartDate, EndDate)VALUES
(9, 1, 5, '1-1-2018', '2-1-2018'),
(10, 17, 3, '10-10-2020', '10-20-2020'),
(11, 6, 7, '5-5-2020', '5-5-2020');

SELECT B.FirstName + ' ' + B.LastName, Bk.Title, BB.StartDate, BB.EndDate
FROM Borrowers B, Borrowers_Books BB, (SELECT B.BookId, T.Title
FROM Books B Right JOIN Titles T ON T.TitleId = B.TitleId) Bk
WHERE B.BorrowerId = BB.BorrowerId AND Bk.BookId = BB.BookId

SELECT T.Title, C.FullName
FROM Titles T INNER JOIN  Characters C ON T.TitleId = C.TitleId 

SELECT T.TitleId, T.Title, T2.TopicId, T2.TopicName
FROM Titles T, Topics T2

SELECT TitleId, Title
FROM Titles;

SELECT TopicId, TopicName
FROM Topics

SELECT B.BookId, T.Title, B.LibraryId
FROM Books B JOIN Titles T ON T.TitleId = B.TitleId


--Referential Integrity constraint
--INSERT INTO Cities(RegionId, CityName, CityPopulation) VALUES (-1, '', -1);


-- First update: Return all books borrowed by John Smith (meaning set de end date 
SELECT B.FirstName + ' ' + B.LastName AS 'Full name', BB.BookId, BB.StartDate, BB.EndDate
FROM Borrowers_Books BB INNER JOIN Borrowers B ON BB.BorrowerId = B.BorrowerId
WHERE B.FirstName = 'John' AND B.LastName = 'Smith'

UPDATE Borrowers_Books
SET EndDate = GETDATE()
FROM Borrowers_Books BB INNER JOIN Borrowers B ON BB.BorrowerId = B.BorrowerId
WHERE B.FirstName = 'John' AND B.LastName = 'Smith'


-- Second update: Update the publication year of all 'Amintiri din copilarie' books from 'Humanitas' publishing house
SELECT B.BookId, T.Title, B.PublicationYear, B.PublishingHouse
FROM Books B INNER JOIN Titles T ON B.TitleId = T.TitleId
WHERE T.Title = 'Amintiri din copilarie' AND B.PublishingHouse = 'Humanitas'


UPDATE Books
SET PublicationYear = 1995
FROM Books B INNER JOIN Titles T ON B.TitleId = T.TitleId
WHERE T.Title = 'Amintiri din copilarie' AND B.PublishingHouse = 'Humanitas'


-- Third update: Update the Borrowing popularity: In each region the city with the highest population has 'HIGH' popularity
-- The city with lowest population has low popularity

SELECT C.RegionId, C.CityName, C.CityPopulation, C.BorrowingPopularity
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MAX(CityPopulation) AS 'MaximumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE C.CityPopulation = T.MaximumPopulation

SELECT C.RegionId, C.CityName, C.CityPopulation, C.BorrowingPopularity
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MIN(CityPopulation) AS 'MaximumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE C.CityPopulation = T.MaximumPopulation

UPDATE Cities
SET BorrowingPopularity = 'High'
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MAX(CityPopulation) AS 'MaximumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE C.CityPopulation = T.MaximumPopulation
 
 
UPDATE Cities
SET BorrowingPopularity = 'Low'
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MIN(CityPopulation) AS 'MinimumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE C.CityPopulation = T.MinimumPopulation

UPDATE Cities
SET BorrowingPopularity = 'Medium'
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MAX(CityPopulation) AS 'MaximumPopulation', MIN(CityPopulation) AS 'MinimumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE T.MinimumPopulation < C.CityPopulation AND C.CityPopulation < T.MaximumPopulation

/*
UPDATE Cities
SET BorrowingPopularity = 'None'

SELECT * FROM Cities
*/


-- Delete all libraries which do not have an address or do not have a name

INSERT INTO Libraries(LibraryId, CityId, LibraryAddress, LibraryName, FoundationYear) VALUES
(20, 9, NULL, 'Biblioteca1', 2000),
(21, 9, NULL, NULL, 2000),
(22, 9, 'addr1', NULL, 2000);

DELETE FROM Libraries
WHERE LibraryAddress IS NULL OR LibraryName IS NULL;

SELECT * FROM Libraries

-- Delete all 'unrealistic topics'

INSERT INTO Topics(TopicId, TopicName) VALUES
(50, 'Unrealistic War'),
(60, 'Unrealistic Cookbook'),
(70, 'SF Unrealistic'),
(80, 'Unrealistic'),
(90, 'Very unrealistic topic');

SELECT * FROM Topics

DELETE FROM Topics
WHERE TopicName LIKE '%unrealistic%'
