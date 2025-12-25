const router = require('express').Router();

// Rutas de los POSTS y AUTORES
router.use('/posts', require('./api/posts.routes'));
router.use('/autores', require('./api/autores.routes'));

module.exports = router;
