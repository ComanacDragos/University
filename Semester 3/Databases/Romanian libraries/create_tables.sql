--USE RomanianLibrariesDB

CREATE TABLE Regions
(
	RegionId INT PRIMARY KEY,
	Name VARCHAR(50)
);

CREATE TABLE Cities
(
	CityId INT PRIMARY KEY,
	RegionId INT REFERENCES Regions(RegionId),
	CityName VARCHAR(50),
	CityPopulation INT
);

ALTER TABLE Cities
ADD BorrowingPopularity VARCHAR(6) DEFAULT 'Medium' WITH VALUES

CREATE TABLE Libraries
(
	LibraryId INT PRIMARY KEY,
	CityId INT REFERENCES Cities(CityId),
	LibraryAddress VARCHAR(100),
	LibraryName VARCHAR(50),
	FoundationYear INT
);

CREATE TABLE Titles
(
	TitleId INT PRIMARY KEY,
	Title VARCHAR(100)
);

CREATE TABLE Books
(
	BookId INT PRIMARY KEY,
	LibraryId INT REFERENCES Libraries(LibraryId),
	TitleId INT REFERENCES Titles(TitleId),
	Pages INT,
	IBSN VARCHAR(20),
	PublicationYear INT,
	PublishingHouse VARCHAR(50)
);

CREATE TABLE Characters
(
	CharacterId INT PRIMARY KEY,
	TitleId INT REFERENCES Titles(TitleId),
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
	TopicId INT PRIMARY KEY,
	TopicName Varchar(50)
);

CREATE TABLE Borrowers
(
	BorrowerId INT PRIMARY KEY,
	CityId INT REFERENCES Cities(CityId),
	FirstName VARCHAR(50),
	LastName VARCHAR(50),
	DateOfBirth DATE,
	Gender CHAR
);

CREATE TABLE Authors_Titles
(
	AuthorId INT REFERENCES Authors(AuthorId),
	TitleId INT REFERENCES Titles(TitleId),
	ContributionPercentage INT CHECK(ContributionPercentage > 0 AND ContributionPercentage <= 100),
	PRIMARY KEY (AuthorId, TitleId)

);

CREATE TABLE Topics_Titles
(
	TopicId INT REFERENCES Topics(TopicId),
	TitleId INT REFERENCES Titles(TitleId),
	TopicPercentage INT CHECK(TopicPercentage > 0 AND TopicPercentage <= 100),
	PRIMARY KEY (TopicId, TitleId)
);

CREATE TABLE Borrowers_Books
(
	BorrowerBookId INT PRIMARY KEY,
	BookId INT REFERENCES Books(BookId),
	BorrowerId INT REFERENCES Borrowers(BorrowerId),
	StartDate DATE NOT NULL,
	EndDate DATE, CHECK(EndDate >= StartDate)
);

/*
DROP TABLE Topics_Titles;
DROP TABLE Borrowers_Books;
DROP TABLE Authors_Titles;


DROP TABLE Topics;
DROP TABLE Characters;
DROP TABLE Books;
DROP TABLE Titles;
DROP TABLE Libraries;

DROP TABLE Borrowers;
DROP TABLE Authors;

DROP TABLE Cities;

DROP TABLE Regions;
*/
