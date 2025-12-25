const AutoresModel = require('../models/autores.model');

//Checkea si el ID del AUTOR es valido
const checkAutoresId = async (req, res, next) => {
    const { autorId } = req.params;

    //Si el id no es un numero
    if(isNaN(autorId)){
        return res.status(400).json({ message: 'El id del autor debe ser un numero'});
    }

    //Comprobar si el id del autor existe en la base de datos
    const autor = await AutoresModel.selectById(autorId);
    if(!autor) return res.status(404).json({ message: 'No existe un autor con ese id' });

    req.autor = autor;
    
    next();
}

module.exports = { checkAutoresId }