SELECT @@TRANCOUNT as 'TransactionCount', @@SPID as 'SessionID'

DBCC USEROPTIONS

SELECT resource_type, request_mode, request_type, request_status, request_session_id
FROM sys.dm_tran_locks
WHERE request_owner_type = 'TRANSACTION'

--reproduce the following concurrency issues under pessimistic isolation 
-- levels: dirty reads, non-repeatable reads, phantom reads, and a deadlock 
-- (4 different scenarios); 
-- you can use stored procedures and / or stand-alone queries;
-- find solutions to solve / workaround the concurrency issues

DELETE FROM Regions
DELETE FROM Cities
INSERT INTO Regions (RegionId, Name) VALUES
(1, 'region1')

INSERT INTO Cities (CityId, CityName) VALUES
(1, 'city1')

SELECT * FROM Regions
SELECT * FROM Cities

SELECT * FROM ChangesLog
ORDER BY currentTime
SELECT * FROM LocksLog
ORDER BY currentTime DESC

BEGIN TRAN
	EXEC sp_log_locks @info = 'deadlock1 - before update'

	UPDATE Regions
	SET Name = 'deadlockRegion1'
	OUTPUT GETDATE(), 'deadlock1 - update', deleted.Name, inserted.Name, NULL
	INTO ChangesLog
	WHERE RegionId = 1
	
	EXEC sp_log_locks @info = 'deadlock1 - between updates'

	WAITFOR DELAY '00:00:05'
	
	UPDATE Cities
	SET CityName = 'deadlockCity1'
	OUTPUT GETDATE(), 'deadlock1 - update', deleted.CityName, inserted.CityName, NULL
	INTO ChangesLog
	WHERE CityId = 1

	EXEC sp_log_locks @info = 'deadlock1 - after update'
COMMIT TRAN