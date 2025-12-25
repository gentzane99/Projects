const AutoresModel = require('../models/autores.model');

//Controlador para obtener todos los AUTORES
const getAll = async (req, res) => {
    const autores = await AutoresModel.selectAutores();
    res.json(autores);
}

//Controlador para obtener un AUTOR por ID
const getById = async (req, res) => {
    res.json(req.autor);
}

//Controlador para obtener todos los POST de un AUTOR por ID
const getAutorPostsById = async (req, res) => {
    const posts = await AutoresModel.selectAutorPosts(req.autor.id);
    res.json(posts);
}

//Controlador para crear un AUTOR por ID
const create = async (req, res) => {
    const {insertId} = await AutoresModel.insertAutores(req.body);
    const autor = await AutoresModel.selectById(insertId);
    res.json(autor);
}

module.exports = { getAll, getById, getAutorPostsById ,create }
