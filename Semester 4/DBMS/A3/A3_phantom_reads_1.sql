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

SELECT * FROM ChangesLog
ORDER BY currentTime
SELECT * FROM LocksLog
ORDER BY currentTime DESC

BEGIN TRAN
	EXEC sp_log_locks @info = 'phantom read - before insert'

	INSERT INTO Regions (RegionId, Name) 
	OUTPUT GETDATE(), 'phantom read - insert', NULL, inserted.Name, NULL
		INTO ChangesLog
	VALUES (2, 'phantom region')
	
	EXEC sp_log_locks @info = 'phantom read - after insert'
COMMIT TRAN