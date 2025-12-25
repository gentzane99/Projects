const router = require("express").Router();
const { getAll, getById, getAutorPostsById ,create} = require("../../controllers/autores.controller");
const { checkAutoresId } = require("../../middlewares/autores.middlewares");
const { validateSchema } = require("../../middlewares/validation.middlewares");
const { autorSchema } = require("../../schemas/autor.schema");

//Metodos GET AUTOR
router.get("/", getAll);
router.get("/:autorId", checkAutoresId, getById);
router.get("/:autorId/posts", checkAutoresId, getAutorPostsById);

//Metodos POST AUTOR
router.post("/", validateSchema(autorSchema), create);

module.exports = router;
