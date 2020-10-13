SELECT * FROM Regions

INSERT INTO Regions(RegionId, Name) 
VALUES (1, 'Transilvania');

INSERT INTO Regions(RegionId, Name) VALUES
(2, 'Moldova'),
(3, 'Tara Romaneasca');	


SELECT * FROM Cities

INSERT INTO Cities(CityId, RegionId, Name, Population) VALUES
(1, 1, 'Cluj-Napoca', 706905),
(2, 1, 'Sibiu', 401000),
(3, 1, 'Timisoara', 306000),
(4, 2, 'Botosani', 107000),
(5, 2, 'Piatra-Neamt', 104000),
(6, 2, 'Suceava', 106500),
(7, 2, 'Iasi', 700000),
(8, 3, 'Bucuresti', 2419400),
(9, 3, 'Constanta', 673000);


SELECT * FROM Topics

INSERT INTO Topics(TopicName) VALUES
('Drama'),
('Science Fiction');


SELECT * FROM Libraries

INSERT INTO Libraries(LibraryId, CityId, LibraryAddress, LibraryName, ConstructionDate) VALUES
(1, 1, 'Str. Clinicilor 2', 'Biblioteca Centrala Universitara Lucian Blaga', '1-1-1872'),
(2, 1, 'Str. Calea Dorobantilor 104', 'Biblioteca Judeteana Octavian Goga', '1-1-1921');



INSERT INTO Libraries VALUES
(3, 1, '', '', '1-1-2000')
INSERT INTO Cities VALUES
(10, 3, 'Inexistent city', 0);

DELETE FROM Libraries
WHERE LibraryId = 3;

DELETE FROM Cities
WHERE Name = 'Inexistent City'

UPDATE Cities
SET Population = 706900
WHERE Name = 'Cluj-Napoca';

UPDATE Topics
SET TopicName='SF'
WHERE TopicId = 2;

UPDATE Libraries
SET ConstructionDate = '1-2-1872'
WHERE LibraryId = 1