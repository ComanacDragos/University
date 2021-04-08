USE Libraries
GO

GO
CREATE PROCEDURE sp_insert_author_title 
	@title VARCHAR(100),
	@contributionPercentage INT,
	@firstName VARCHAR(50),
	@lastName VARCHAR(50),
	@DOB date
AS 
BEGIN
	DECLARE @authorId INT, @titleId INT;

	SELECT @authorId = MaxAuthorId + 1
	FROM (
		SELECT MAX(AuthorId) as MaxAuthorId
		FROM Authors
	) t
END
GO