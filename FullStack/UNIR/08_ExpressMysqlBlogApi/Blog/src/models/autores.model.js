const db = require('../config/db');

//Obtiene todos los AUTORES de la BBDD
const selectAutores = async () => {
    const [result] = await db.query('select * from autores');
    return result; //array con todos los autores
}

//Obtiene un AUTOR por ID de la BBDD
const selectById = async (autoresId) => {
    const [result] = await db.query('select * from autores where id = ?', [autoresId]);
    if(result.length === 0) return null;
    return result[0];
}

//Obtiene todos los POSTS por ID de AUTOR de la BBDD
const selectAutorPosts = async (autoresId) => {
    const [result] = await db.query('select * from posts where idAutores = ?', [autoresId]);
    if(result.length === 0) return null;
    return result;
}

//Inserta un nuevo AUTOR en la BBDD
const insertAutores = async ({ nombre, email, imagen }) => {
    const [result] = await db.query('insert into autores (nombre, email, imagen) values (?, ?, ?)', 
                                    [nombre, email, imagen]
    );
    return result;
}

module.exports = { selectAutores, selectById, selectAutorPosts ,insertAutores };
