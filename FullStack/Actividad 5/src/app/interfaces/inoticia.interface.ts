/*
  File: inoticia.interface.ts
  Author: Gentzane Pastor
  Date: 13/07/2025
  Description: Define la interfaz de noticia.
*/

//Interfaz que representa la forma que tiene cada noticia del blog
export interface INoticia {
    id: number;
    titulo: string;
    img: string;
    texto: string;
    fecha: string;
}
