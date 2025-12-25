const router = require('express').Router();
const { getAll, getById, create} = require('../../controllers/posts.controller');
const { checkPostsId, checkAutorIdExists } = require('../../middlewares/posts.middlewares copy');
const { validateSchema } = require("../../middlewares/validation.middlewares");
const { postSchema } = require("../../schemas/post.schema");

//Metodos GET POSTS
router.get('/', getAll);
router.get('/:postId', checkPostsId, getById);

//Metodo POST POSTS
router.post('/', checkAutorIdExists, validateSchema(postSchema), create);

module.exports = router;
