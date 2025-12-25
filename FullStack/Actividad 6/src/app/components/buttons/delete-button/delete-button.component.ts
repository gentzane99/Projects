import { Component, EventEmitter, inject, input, Output } from '@angular/core';
import { IUser } from '../../../interfaces/iuser.interface';
import { UsersService } from '../../../services/users.service';
import Swal from 'sweetalert2';
@Component({
    selector: 'app-delete-button',
    imports: [],
    templateUrl: './delete-button.component.html',
    styleUrl: './delete-button.component.css'
})
export class DeleteButtonComponent {
    miUser = input<IUser>()
    text = input<string>("Borrar")
    visible = input<boolean>(true)
    userService = inject(UsersService)

    @Output() deleteUserEmit: EventEmitter<string> = new EventEmitter()

    async deleteUser(){

        const result = await Swal.fire({
          text: `¿Deseas Borrar al usuario ${this.miUser()?.first_name}?`,
          showCancelButton: true,
          confirmButtonColor: "#3085d6",
          cancelButtonColor: "rgba(182, 182, 182, 1)",
          confirmButtonText: "Aceptar",
          cancelButtonText: "Cancelar",
          reverseButtons: true,
          showCloseButton: true,
          padding: "1em"
        });

        if (result.isConfirmed) {
            const user = this.miUser();
            if (user?._id) {
                const response: any =  await this.userService.remove(user._id);
                if(!response.error){
                    this.deleteUserEmit.emit('Usuario borrado correctamente')
                } else{
                    console.log(response)
                }
            }
        }
    }
}
