## APP consulatando a API externa
- Usar boostrap como framework de css.
    

- Averiguar cuantos componentes necesitamos y crearlos.
- Crear el sistema de rutas para cada componente.
- Crear componentes hijos si lo consideras necesario.
- Comunicar los componentes a través de los medios necesarios para que los datos lleguen a cada uno de los elementos.
- El trabajo con formularios y validaciones.


Url api: 
    https://peticiones.online/users 
    - entidades: Usuario 
    - IMPORTANTE: Usar el _id no el id
    - {
        "_id",
        "id"
        "first_name",
        "last_name",
        "username",
        "email",
        "image",
        "password"
    }
Componentes: -Pages
-Publica
    - HOME => /home => HomeComponent - Grid de usuarios donde se muestra la foto del usuario, el nombre y tres botones de Ver detalle, Borrar y Actualizar.
    - USER => /user/:idUser => UserComponent - Vista del usuario correspondiente con el id y sus datos
    - NEW USER => /newuser => NewUserComponent - Formulario para dar el alta a un usuario
    - UPDATE USER => /updateuser/:idUser =>UpdateUserComponent - Formulario de new user que se usara para actualizar los datos del user del id correspondiente
Services:
    Users
Interfaces:
    IUser