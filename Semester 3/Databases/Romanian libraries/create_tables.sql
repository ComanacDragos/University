CREATE TABLE Regions
(
	RegionId INT PRIMARY KEY,
	Name VARCHAR(50)
);

CREATE TABLE Cities
(
	CityId INT PRIMARY KEY IDENTITY(1,1),
	RegionId INT REFERENCES Regions(RegionId),
	CityName VARCHAR(50),
	CityPopulation INT
);

CREATE TABLE Libraries
(
	LibraryId INT PRIMARY KEY IDENTITY(1, 1),
	CityId INT REFERENCES Cities(CityId),
	LibraryAddress VARCHAR(100),
	LibraryName VARCHAR(50),
	FoundationDate DATE
);

ALTER TABLE Libraries
DROP COLUMN FoundationDate;

ALTER TABLE Libraries
ADD FoundationYear INT;

CREATE TABLE Books
(
	BookId INT PRIMARY KEY IDENTITY(1, 1),
	LibraryId INT REFERENCES Libraries(LibraryId),
	Title VARCHAR(100),
	Pages INT,
	IBSN VARCHAR(20),
	PublicationDate DATE,
	PublishingHouse VARCHAR(50)
);

ALTER TABLE Books
DROP COLUMN PublicationDate

ALTER TABLE Books
ADD PublicationYear INT

CREATE TABLE Characters
(
	CharacterId INT PRIMARY KEY,
	FullName VARCHAR(50),
	CharacterRole VARCHAR(50)
);

CREATE TABLE Authors
(
	AuthorId INT PRIMARY KEY,
	FirstName VARCHAR(50), 
	LastName VARCHAR(50),
	DOB DATE
);

CREATE TABLE Topics
(
	TopicId INT PRIMARY KEY IDENTITY (1,1),
	TopicName Varchar(50)
);

CREATE TABLE Borrowers
(
	BorrowerId INT PRIMARY KEY,
	CityId INT REFERENCES Cities(CityId),
	FirstName VARCHAR(50),
	LastName VARCHAR(50),
	DateOfBirth DATE,
	Gender VARCHAR(6)
);

CREATE TABLE Authors_Books
(
	AuthorId INT REFERENCES Authors(AuthorId),
	BookId INT REFERENCES Books(BookId),
	PRIMARY KEY (AuthorId, BookId)
);

CREATE TABLE Topics_Books
(
	TopicId INT REFERENCES Topics(TopicId),
	BookId INT REFERENCES Books(BookId),
	PRIMARY KEY (TopicId, BookId)
);

CREATE TABLE Borrowers_Books
(
	BorrowerBookId INT PRIMARY KEY,
	BookId INT REFERENCES Books(BookId),
	BorrowerId INT REFERENCES Borrowers(BorrowerId),
	StartDate DATE NOT NULL,
	EndDate DATE
);

CREATE TABLE Characters_Books
(
	CharacterId INT REFERENCES Characters(CharacterId),
	BookId INT REFERENCES Books(BookId),
	PRIMARY KEY (CharacterId, BookId)
)

/*
DROP TABLE Topics_Books;
DROP TABLE Borrowers_Books;
DROP TABLE Authors_Books;
DROP TABLE Characters_Books

DROP TABLE Topics;
DROP TABLE Characters;
DROP TABLE Books;
DROP TABLE Libraries;

DROP TABLE Borrowers;
DROP TABLE Authors;

DROP TABLE Cities;

DROP TABLE Regions;
*/