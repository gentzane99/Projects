const yup = require('yup');

const postSchema = yup.object({
    titulo: yup
            .string()
            .required('El titulo es requerido'),

    descripcion: yup
           .string()
           .required('La descripcion es requerida'),

    categoria: yup
            .string()
            .required('La categoria es requerida'),
    idAutores: yup
               .number()
               .required('El id del autor es requerido')
});

module.exports = { postSchema }