const db = require('../config/db');

//Obtiene todos los POSTS  de la BBDD
const selectPosts = async () => {
    const [result] = await db.query('select * from posts');
    return result; //array con todos los posts
}

//Obtiene un POST por ID de la BBDD
const selectById = async (postsId) => {
   const [result] = await db.query('select * from posts where id = ?', [postsId]);
   if(result.length === 0) return null;
   return result[0];
}

//Inserta un nuevo POST en la BBDD
const insertPosts = async ({ titulo, descripcion, categoria, idAutores }) => {
    const [result] = await db.query('insert into posts (titulo, descripcion, categoria, idAutores) values (?, ?, ?, ?)', 
                                    [titulo, descripcion, categoria, idAutores]
    );
    return result;
}

module.exports = { selectPosts, selectById ,insertPosts};