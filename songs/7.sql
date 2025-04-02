SELECT avg(energy) FROM songs
WHERE artist_id in(
    SELECT id FROM artists
    WHERE name ='Drake'
);
