CREATE TABLE Regions
(
	RegionId INT PRIMARY KEY,
	Name VARCHAR(50)
);

CREATE TABLE Cities
(
	CityId INT PRIMARY KEY,
	RegionId INT REFERENCES Regions(RegionId),
	Name VARCHAR(50),
	Population INT
);

CREATE TABLE Libraries
(
	LibraryId INT PRIMARY KEY,
	CityId INT REFERENCES Cities(CityId),
	LibraryAddress VARCHAR(100),
	LibraryName VARCHAR(50),
	ConstructionData DATE
);

CREATE TABLE Books
(
	BookId INT PRIMARY KEY,
	LibraryId INT REFERENCES Libraries(LibraryId),
	Title VARCHAR(50),
	Pages INT,
	IBSN VARCHAR(20)
);

CREATE TABLE Characters
(
	CharacterId INT PRIMARY KEY,
	BookId INT REFERENCES Books(BookId),
	FullName VARCHAR(50),
	CharacterRole VARCHAR(50)
);

CREATE TABLE Authors
(
	AuthorId INT PRIMARY KEY,
	CityId INT REFERENCES Cities(CityId),
	FirstName VARCHAR(50), 
	LastName VARCHAR(50),
	Age INT
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

CREATE TABLE Borrower_Books
(
	BookId INT REFERENCES Books(BookId),
	BorrowerId INT REFERENCES Borrowers(BorrowerId),
	PRIMARY KEY (BookId, BorrowerId),
	StartDate DATE NOT NULL,
	EndDate DATE
);