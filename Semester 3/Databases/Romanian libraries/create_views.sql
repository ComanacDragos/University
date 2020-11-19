--a view with a SELECT statement operating on one table;
--DROP VIEW HighlyPopulatedCitiesView
GO
CREATE VIEW HighlyPopulatedCitiesView
AS
SELECT CityId, CityName, CityPopulation
FROM Cities
WHERE CityPopulation > 300000
GO
SELECT * FROM HighlyPopulatedCitiesView

--a view with a SELECT statement operating on at least 2 tables;
--DROP VIEW LibrariesAndCitiesView
GO
CREATE VIEW LibrariesAndCitiesView
AS
SELECT L.LibraryId, L.LibraryName, C.CityId, C.CityName
FROM Libraries L INNER JOIN Cities C ON L.CityId = C.CityId
GO
SELECT * FROM LibrariesAndCitiesView

--a view with a SELECT statement that has a GROUP BY clause and operates on at least 2 tables.
--DROP NumberOfLibrariesInEachCityView
GO
CREATE VIEW NumberOfLibrariesInEachCityView
AS
SELECT C.CityName, COUNT(L.LibraryName) AS 'Number of libraries'
FROM Libraries L INNER JOIN Cities C ON L.CityId = C.CityId
GROUP BY C.CityName
GO
SELECT * FROM NumberOfLibrariesInEachCityView
