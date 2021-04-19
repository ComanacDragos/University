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
	logId INT PRIMARY KEY IDENTITY(1, 1),
	currentTime DATETIME, 
	
	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100), 
	request_status VARCHAR(100),
	request_session_id INT
)



-- DROP PROCEDURE sp_log_locks
GO
CREATE PROCEDURE sp_log_locks
AS 
BEGIN 
	INSERT INTO LocksLog (currentTime, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), resource_type, request_mode, request_type, request_status, request_session_id
	FROM sys.dm_tran_locks
	WHERE request_owner_type = 'TRANSACTION'
	
END
GO

-- DROP PROCEDURE sp_log_changes
GO
CREATE PROCEDURE sp_log_changes
	@oldData VARCHAR(100),
	@newData VARCHAR(100)
AS 
BEGIN
	INSERT INTO ChangesLog (currentTime, oldData, newData) VALUES
	(GETDATE(), @oldData, @newData)
END
GO

SELECT * FROM ChangesLog

SELECT * FROM LocksLog