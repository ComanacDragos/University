INSERT INTO Regions(RegionId, Name) VALUES
(1, 'Transilvania'),
(2, 'Moldova'),
(3, 'Tara Romaneasca');	

SELECT * FROM Regions

INSERT INTO Cities(RegionId, CityName, CityPopulation) VALUES
(1, 'Cluj-Napoca', 706905),
(1, 'Sibiu', 401000),
(1, 'Timisoara', 306000),
(2, 'Botosani', 107000),
(2, 'Piatra-Neamt', 104000),
(2, 'Suceava', 106500),
(2, 'Iasi', 700000),
(3, 'Bucuresti', 2419400),
(3, 'Constanta', 673000);

SELECT * FROM Cities

INSERT INTO Topics(TopicName) VALUES
('Drama'),
('Science Fiction'),
('Romance'),
('Survival'),
('Power and corruption'),
('Family'),
('Rural'),
('Urban'),
('Biography'),
('History'),
('War'),
('Fiction'),
('Action'),
('Adventure'),
('Comic'),
('Classic'),
('Mystery'),
('Fantasy'),
('Horror'),
('Thriller'),
('Cookbook'),
('Philosophy');

SELECT * FROM Topics

INSERT INTO Libraries(CityId, LibraryAddress, LibraryName, FoundationYear) VALUES
(1, 'Str. Clinicilor 2', 'Biblioteca Centrala Universitara Lucian Blaga', 1872),
(1, 'Str. Calea Dorobantilor 104', 'Biblioteca Judeteana Octavian Goga', 1921),
(2, 'Str. George Baritiu', 'Biblioteca Judeteana Astra', 1963),
(2, 'Str. Lucian Blaga 2A', 'Biblioteca Centrala a Universitatii', 1969),
(3, 'Piata Libertatii nr. 3', 'Biblioteca Judeteana Timis', 1904),
(4, 'Calea Nationala 62', 'Biblioteca Judeteana Mihai Eminescu', 1882),
(5, 'Bulevardul Republicii 15A', 'Biblioteca Judeteana G.T. Kirileanu', 1869),
(6, 'Bulevardul Stefan Cel Mare', 'Biblioteca I.G. SBIERA', 1923),
(7, 'Str. Pacurari nr 4', 'Biblioteca Centrala Universitara Mihai Eminescu', 1835),
(8, 'Bulevardul Unirii 22', 'Biblioteca Nationala a Romaniei', 1859),
(9, 'Str. Mircea cel Batran 104A', 'Bibliteca Judeteana Ioan N. Roman', 1931);

SELECT * FROM Libraries

INSERT INTO Books(LibraryId, Title, Pages, IBSN, PublicationYear, PublishingHouse) VALUES
(1, 'Un veac de singuratate', 480, '978-973-103-462-1', 1967, 'Rao'),
(1, 'Noaptea de Sanziene', 645, NULL, 1955, 'Editions Gallimard'),
(2, 'Jurnalul unui mag', 200, '543-785-123-876-2', 1987, 'Humanitas'),
(3, 'Amintiri din copilarie', 50, NULL, 1892, 'Humanitas'),
(3, 'Un veac de singuratate', 500, '978-973-103-462-1', 1967, 'Humanitas'),
(4, 'Nunta in cer', 200, '959-200-443-123-4', 1938, 'Adevarul'),
(5, 'Silogismele Amaraciunii', 100, NULL, 1984, 'Humanitas'),
(5, 'Noaptea de Sanziene', 685, NULL, 1955, 'Albatros'),
(6, 'Tratat de Descompunere', 200, '298-263-696-223-1', 1949, 'Humanitas'),
(6, 'Un veac de singuratate', 529, '178-373-463-462-1', 1967, 'Humanitas'),
(7, 'Romanul adolescentului miop', 300, '423-875-195-023-2', 1989, 'Minerva'),
(7, 'Amintiri din copilarie', 50, NULL, 1892, 'Albatros'),
(8, 'Fratii Jderi', 1000, '843-678-232-123-1', 1892, 'Minerva'),
(9, 'Din Calidor', 100, NULL, 1987, 'Albatros'),
(9, 'Nunta in cer', 230, '312-230-343-223-4', 1938, 'Adevarul'),
(10, 'Noaptea de Sanziene', 645, NULL, 1955, 'Editions Gallimard'),
(10, 'Jurnalul unui mag', 200, '443-385-223-576-7', 1987, 'Humanitas'),
(10, 'Amintiri din copilarie', 50, NULL, 1892, 'Humanitas'),
(10, 'Un veac de singuratate', 500, '148-173-103-462-1', 1967, 'Humanitas'),
(11, 'Maitreyi', 100, '234-432-654-753-0', 1933, 'Humanitas');

SELECT * FROM Books

INSERT INTO Authors(AuthorId, FirstName, LastName, DOB) VALUES
(1, 'Gabriel Garcia', 'Marquez', '03-06-1927'),
(2, 'Mircea', 'Eliade', '03-13-1907'),
(3, 'Emil', 'Cioran', '04-08-1911'),
(4, 'Paulo', 'Coelho', '08-24-1947'),
(5, 'Ion', 'Creanga', '03-01-1837'),
(6, 'Mihail', 'Sadoveanu', '11-05-1880');

SELECT * FROM Authors 




INSERT INTO Libraries VALUES
(1, '', '', '1-1-2000')
INSERT INTO Cities VALUES
(3, 'Inexistent city', 0);

DELETE FROM Libraries
WHERE LibraryId = 3;

DELETE FROM Cities
WHERE CityName = 'Inexistent City'

UPDATE Cities
SET CityPopulation = 706900
WHERE CityName = 'Cluj-Napoca';

UPDATE Topics
SET TopicName='SF'
WHERE TopicId = 2;

UPDATE Libraries
SET FoundationDate = '1-2-1872'
WHERE LibraryId = 1