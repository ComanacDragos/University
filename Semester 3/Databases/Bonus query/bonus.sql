WITH f(n, i) AS(
	SELECT 1, 1
	UNION ALL
	SELECT n * i, i + 1
	FROM f
)
SELECT TOP 5 n FROM f
s
