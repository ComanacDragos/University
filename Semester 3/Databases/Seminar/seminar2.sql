USE RomanianLibrariesDB

SELECT C.RegionId, C.CityName, C.CityPopulation, C.BorrowingPopularity
FROM Cities C INNER JOIN (
SELECT RegionId AS 'RegionId', MAX(CityPopulation) AS 'MaximumPopulation'
FROM Cities
GROUP BY RegionId
) T ON C.RegionId = T.RegionId
WHERE C.CityPopulation = T.MaximumPopulation

