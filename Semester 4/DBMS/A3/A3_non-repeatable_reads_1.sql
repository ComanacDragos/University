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
	
	EXEC sp_log_locks @info = 'non-repeatable read - before update'

	UPDATE Regions
	SET Name = 'Dirty region'
	OUTPUT GETDATE(), 'non-repeatable read - update', deleted.Name, inserted.Name, NULL
	INTO ChangesLog
	WHERE RegionId = 1

	EXEC sp_log_locks @info = 'non-repeatable read - after update'
COMMIT