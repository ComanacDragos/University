CREATE DATABASE Ex1
GO
USE 
Ex1

CREATE TABLE Customers(
	customerId INT PRIMARY KEY,
	name VARCHAR (50),
	DOB DATE
);

INSERT INTO Customers VALUES
(1, 'c1', '1-1-2000'),
(2, 'c2', '1-2-2000'),
(3, 'c3', '1-3-2000');

CREATE TABLE BankAccounts(
	bankAccountId INT PRIMARY KEY,
	customerId INT FOREIGN KEY REFERENCES Customers(customerId),
	IBAN VARCHAR(100),
	balance INT
);

INSERT INTO BankAccounts VALUES
(1, 1, 'IBAN1', 1000),
(2, 2, 'IBAN2', 2000),
(3, 3, 'IBAN3', 3000),
(4, 1, 'IBAN4', 4000)

CREATE TABLE Cards(
	cardId INT PRIMARY KEY,
	bankAccountId INT FOREIGN KEY REFERENCES BankAccounts(bankAccountId),
	number VARCHAR(20),
	CVV INT
);

INSERT INTO Cards VALUES
(1, 1, '1111 1111 1111 1111', 111),
(2, 2, '2222 2222 2222 2222', 222),
(3, 3, '3333 3333 3333 3333', 333),
(4, 4, '4444 4444 4444 4444', 444)


CREATE TABLE ATMS(
	atmId INT PRIMARY KEY,
	address VARCHAR(100)
);

INSERT INTO ATMS VALUES
(1, 'a1'),
(2, 'a2')

CREATE TABLE Transactions(
	transactionId INT PRIMARY KEY,
	atmId INT FOREIGN KEY REFERENCES ATMS(atmId),
	cardId INT FOREIGN KEY REFERENCES Cards(cardId),
	amount INT,
	date_time DATETIME
);

INSERT INTO Transactions VALUES
(6,1, 1, 100, '1-1-2000 5:15'),
(7,1, 1, 50, '1-1-2000 5:10'),

(1,1, 4, 2005, '5-5-2000 8:11'),
(2,2, 3, 1001, '4-4-2000 7:15'),
(3,1, 3, 1000, '4-4-2000 7:10'),
(4,2, 2, 200, '3-3-2000 6:15'),
(5,1, 2, 100, '1-1-2000 6:10')

SELECT * FROM Transactions

GO
CREATE PROCEDURE sp_delete_transactions_for_card @cardId INT
AS
BEGIN
	DELETE FROM Transactions
	WHERE cardId = @cardId
END
GO

sp_delete_transactions_for_card 1

GO
CREATE VIEW cards_all_atms
AS
	SELECT TC.number AS 'CardNumber'
	FROM (SELECT DISTINCT C.number, C.cardId, T.atmId FROM Cards C INNER JOIN Transactions T ON C.cardId = T.cardId) TC
	GROUP BY TC.cardId, TC.number
	HAVING COUNT(*) = (SELECT COUNT(*) FROM ATMS)
GO
SELECT * FROM cards_all_atms

GO
CREATE FUNCTION cards_with_sum ()
RETURNS TABLE
AS
	RETURN
		SELECT C.number, C.CVV
		FROM Cards C INNER JOIN Transactions T ON C.cardId = T.cardId
		GROUP BY C.number, C.CVV
		HAVING SUM(T.amount) >2000
GO

SELECT * FROM cards_with_sum()