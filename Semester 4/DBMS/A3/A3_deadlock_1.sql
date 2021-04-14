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

BEGIN TRAN

	UPDATE Regions
	SET Name = 'deadlockRegion1'
	WHERE RegionId = 1
	
	WAITFOR DELAY '00:00:05'
	
	UPDATE Cities
	SET CityName = 'deadlockCity1'
	WHERE CityId = 1

COMMIT TRAN