SELECT movies.title
FROM movies JOIN ratings
ON movies.id =ratings.movie_id
WHERE id IN(
    SELECT stars.movie_id FROM stars
    WHERE stars.person_id IN(
        SELECT people.id FROM people
        WHERE name = 'Chadwick Boseman'
    )
)ORDER BY ratings.rating DESC
LIMIT 5;
