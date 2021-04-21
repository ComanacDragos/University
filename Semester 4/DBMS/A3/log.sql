SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

DBCC USEROPTIONS

SELECT GETDATE(), resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'



SELECT * --resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks

SELECT GETDATE()

/*
DROP TABLE LocksLog
DROP TABLE ChangesLog
*/

CREATE TABLE LocksLog(
	currentTime DATETIME,
	info VARCHAR(100),
	
	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100), 
	request_status VARCHAR(100),
	request_session_id INT
)

CREATE TABLE ChangesLog(
	currentTime DATETIME,
	info VARCHAR(100),
	oldData VARCHAR(100),
	newData VARCHAR(100),
	error VARCHAR(1000)
)

DELETE FROM LocksLog
DELETE FROM ChangesLog

-- DROP PROCEDURE sp_log_locks
GO
CREATE PROCEDURE sp_log_locks
	@info VARCHAR(100)
AS 
BEGIN 
	INSERT INTO LocksLog (currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id
	FROM sys.dm_tran_locks
	WHERE request_owner_type = 'TRANSACTION'
	
END
GO

-- DROP PROCEDURE sp_log_changes
GO
CREATE PROCEDURE sp_log_changes
	@oldData VARCHAR(100),
	@newData VARCHAR(100),
	@info VARCHAR(100),
	@error VARCHAR(100)
AS 
BEGIN
	INSERT INTO ChangesLog (currentTime, oldData, newData, error, info) VALUES
	(GETDATE(), @oldData, @newData, @error, @info)
END
GO


SELECT * FROM LocksLog
SELECT * FROM ChangesLog

--EXECUTE sp_log_locks