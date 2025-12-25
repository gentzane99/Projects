--  Insertar un usuario.
INSERT INTO usuarios (nombre, email, contraseña) 
VALUES ("Gentzane", "gentzane@gmail.com", "1234");

-- Insertar un artista.
INSERT INTO artistas (nombre, foto) 
VALUES ("NIALL HORAN", "https://www.google.com/imgres?q=niall%20horan&imgurl=https%3A%2F%2Fi.scdn.co%2Fimage%2Fab6761610000e5ebeccc1cde8e9fdcf1c9289897&imgrefurl=https%3A%2F%2Fopen.spotify.com%2Fintl-es%2Fartist%2F1Hsdzj7Dlq2I7tHP7501T4&docid=PSNq0l84T5JGWM&tbnid=TNWPtuQyxNbihM&vet=12ahUKEwj7rtWxu6GQAxUqgf0HHeB1AecQM3oECCoQAA..i&w=640&h=640&hcb=2&ved=2ahUKEwj7rtWxu6GQAxUqgf0HHeB1AecQM3oECCoQAA");

-- Insertar un álbum.
INSERT INTO albumes (titulo, discografia, año, artistas_id) 
VALUES ("The Show", "Capitol Records", 2023, 1);

-- Insertar tres canciones.
INSERT INTO canciones (titulo, genero, año, albumes_id) 
VALUES ("Heaven", "Pop", 2023, 1),
	   ("Meltdown", "Pop", 2023, 1),
	   ("The Show", "Pop", 2023, 1);
		
-- Crear una lista con las tres canciones que acabas de dar de alta.
INSERT INTO listas (nombre, usuarios_id) VALUES ("Favoritas", 1);
INSERT INTO lista_canciones(canciones_id, listas_id)
VALUES (1,1),
	   (2,1),
	   (3,1);

-- Registrar que el usuario ha escuchado solo una de las tres canciones.
INSERT INTO canciones_escuchadas_usuarios(canciones_id, usuarios_id)
VALUES (2,1);