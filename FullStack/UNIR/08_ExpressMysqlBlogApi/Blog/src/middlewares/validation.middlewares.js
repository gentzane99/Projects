const validateSchema = (schema) => {
    return async (req, res, next) => {
        try {
            await schema.validate(req.body, { abortEarly: false });
        } catch (error) {
            return res.status(400).json(error.errors);
        }

        next();
    }
}
module.exports =  { validateSchema }