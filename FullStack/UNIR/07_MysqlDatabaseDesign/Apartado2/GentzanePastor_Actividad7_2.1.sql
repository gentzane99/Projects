-- Consulta #1: obtener todas las reservas que tiene el restaurante con id igual 1 para el día 14-03-2024, mostrando los datos del cliente y de la mesa reservada.
SELECT cli.*, m.* FROM reserva resv
INNER JOIN cliente cli ON resv.cliente_id = cli.id
INNER JOIN mesa m ON m.id = resv.mesa_id 
WHERE m.restaurante_id = 1 AND resv.fecha_reserva LIKE "2024-03-14%";

-- Consulta #2: obtener todos los nombres de los restaurantes favoritos y que estén abiertos, para el cliente con id igual a 1.
SELECT rest.nombre FROM restaurante rest
INNER JOIN favorito fav ON restaurante_id=rest.id
WHERE fav.cliente_id = 1 AND rest.is_open = 1;

-- Consulta #3: modificar la fecha y hora de la reserva con id igual a 10 a la siguiente fecha y hora 13-04-2025 18:00.
UPDATE reserva res SET fecha_reserva="2025-04-13 18:00:00" WHERE res.id = 10;

-- Consulta #4: eliminar todos los restaurantes favoritos que no se encuentren abiertos para el cliente con id igual a 1.
DELETE fav FROM favorito fav
INNER JOIN restaurante rest ON fav.restaurante_id=rest.id
WHERE fav.cliente_id = 1 AND rest.is_open = 0;

-- Consulta #5: obtener el nombre de los restaurantes con más de tres reservas de cuatro o más comensales para la fecha 01-04-2024.
SELECT rest.nombre FROM restaurante rest
INNER JOIN mesa m ON restaurante_id = rest.id
INNER JOIN reserva resv ON mesa_id = m.id
WHERE resv.fecha_reserva LIKE "2024-04-01%" AND resv.comensales >=4
GROUP BY rest.nombre HAVING COUNT(resv.id) > 3;

-- Consulta #6: obtener el aforo máximo del restaurante con id igual a 5.
SELECT SUM(m.max_comensales) FROM restaurante rest
INNER JOIN mesa m ON restaurante_id = rest.id
WHERE rest.id = 5;

-- Consulta #7: obtener las mesas que dispongan de espacio para dos comensales y que se encuentren disponibles (sin reserva)
-- en el restaurante con id igual a 5 para la fecha y hora 31-12-2024 19:00.
SELECT m.* FROM mesa m
INNER JOIN restaurante rest ON m.restaurante_id = rest.id
WHERE rest.id=5 AND m.max_comensales >= 2 AND m.id NOT IN (SELECT resv.mesa_id FROM reserva resv WHERE resv.fecha_reserva = "2024-12-31 19:00");

-- Consulta #8: obtener el nombre del cliente que ha realizado más reservas en el restaurante con id igual a 1 entre las fechas 01-01-2024 y 31-12-2024
SELECT cli.nombre FROM reserva resv
INNER JOIN cliente cli ON cli.id = resv.cliente_id
INNER JOIN mesa m ON m.id = resv.mesa_id
WHERE m.restaurante_id = 1 AND resv.fecha_reserva BETWEEN "2024-01-01%" AND "2024-12-31%"
GROUP BY cli.id
ORDER BY COUNT(resv.id) DESC
LIMIT 1;