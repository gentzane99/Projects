const PostsModel = require('../models/posts.model');

//Controlador para obtener todos los POSTS
const getAll = async (req, res) => { 
    const posts = await PostsModel.selectPosts();
    res.json(posts);
}

//Controlador para obtener un POST por ID
const getById = async (req, res) => {
    res.json(req.post);
}

//Controlador para crear un POST
const create = async (req, res) => {
    const {insertId} = await PostsModel.insertPosts(req.body);
    const post = await PostsModel.selectById(insertId);
    res.json(post);
}

module.exports = { getAll, getById, create }
