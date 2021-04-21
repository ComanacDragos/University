USE Libraries
SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'


--reproduce the following concurrency issues under pessimistic isolation 
-- levels: dirty reads, non-repeatable reads, phantom reads, and a deadlock 
-- (4 different scenarios); 
-- you can use stored procedures and / or stand-alone queries;
-- find solutions to solve / workaround the concurrency issues

DELETE FROM Regions
INSERT INTO Regions (RegionId, Name) VALUES
(1, 'region1')

SELECT * FROM Regions

SELECT * FROM LocksLog
SELECT * FROM ChangesLog

DECLARE @auxTable TABLE (
	currentTime DATETIME,
	info VARCHAR(100),
	
	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100), 
	request_status VARCHAR(100),
	request_session_id INT
)

DECLARE @newData TABLE(
		currentTime DATETIME,
		info VARCHAR(100), 
		oldData VARCHAR(100), 
		newData VARCHAR(100),
		error VARCHAR(1000)
	)

BEGIN TRAN

	INSERT INTO @auxTable (currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
		SELECT GETDATE(), 'dirty read - beforeUpdate', resource_type, request_mode, request_type, request_status, request_session_id
		FROM sys.dm_tran_locks
		WHERE request_owner_type = 'TRANSACTION'

	UPDATE Regions
	SET Name = 'Dirty region'
	OUTPUT GETDATE(), 'dirty read - update', deleted.Name, inserted.Name, NULL
	INTO @newData
	WHERE RegionId = 1
	

	INSERT INTO @auxTable (currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
		SELECT GETDATE(), 'dirty read - afterUpdate', resource_type, request_mode, request_type, request_status, request_session_id
		FROM sys.dm_tran_locks
		WHERE request_owner_type = 'TRANSACTION'

	WAITFOR DELAY '00:00:05'
ROLLBACK

INSERT INTO LocksLog (currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT * FROM @auxTable

INSERT INTO ChangesLog
	SELECT * FROM @newData
