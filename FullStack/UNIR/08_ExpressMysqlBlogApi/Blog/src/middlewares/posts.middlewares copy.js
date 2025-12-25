const PostModel = require('../models/posts.model');
const AutorModel = require('../models/autores.model');

//Checkea si el ID del POST es valido
const checkPostsId = async (req, res, next) => {
    const { postId } = req.params;

    //Si el id no es un numero
    if(isNaN(postId)){
        return res.status(400).json({ message: 'El id del post debe ser un numero'});
    }

    //Comprobar si el id del post existe en la base de datos
    const post = await PostModel.selectById(postId);
    if(!post) return res.status(404).json({ message: 'No existe un post con ese id' });

    req.post = post;

    next();
}

//Checkea si el ID del AUTOR es valido
const checkAutorIdExists = async (req, res, next) => {
    const {idAutores} = req.body;

    //Si el id no es un numero
    if(isNaN(idAutores)){
        return res.status(400).json({ message: 'El id del autor debe ser un numero'});
    }

    //Comprobar si el id del autor existe en la base de datos
    const autor = await AutorModel.selectById(idAutores);
    if(!autor) return res.status(404).json({ message: 'No existe un autor con ese id' });

    next();
}

module.exports = { checkPostsId, checkAutorIdExists }