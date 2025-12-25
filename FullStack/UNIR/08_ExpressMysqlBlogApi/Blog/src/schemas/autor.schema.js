const yup = require('yup');

const autorSchema = yup.object({
    nombre: yup
            .string()
            .required('El nombre es requerido'),

    email: yup
           .string()
           .matches(/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/,
           'El email debe tener un formato válido')
           .required('El email es requerido'),

    imagen: yup
            .string()
            .url('La imagen no es una url')
});

module.exports = { autorSchema }