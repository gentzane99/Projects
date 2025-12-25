import { Component, EventEmitter, Output, inject, Input } from '@angular/core';
import { IUser } from '../../interfaces/iuser.interface';
import { UsersService } from '../../services/users.service';
import { DeleteButtonComponent } from '../../components/buttons/delete-button/delete-button.component';
import { UpdateButtonComponent } from '../../components/buttons/update-button/update-button.component';
import { BackToUsersButtonComponent } from '../../components/buttons/back-to-users-button/back-to-users-button.component';
import { Router } from '@angular/router';
import Swal from 'sweetalert2';
@Component({
    selector: 'app-user',
    imports: [DeleteButtonComponent, UpdateButtonComponent, BackToUsersButtonComponent],
    templateUrl: './user.component.html',
    styleUrl: './user.component.css',
})
export class UserComponent {
    @Input() idUser:string = ""
    userService = inject(UsersService);
    miUser?: IUser
    @Output() deleteUserEmit: EventEmitter<string> = new EventEmitter()
    
    router = inject(Router)

    ngOnInit() {
        this.getUser(this.idUser)
    }

    async getUser(id: string) {
       try { 
            const response = await this.userService.getById(id);
            if(response.error){
                this.router.navigate(['/home'])
                Swal.fire({
                position: "bottom-end",
                text: "No se ha podido recuperar el usuario",
                showConfirmButton: false,
                timer: 1500,
                background: "#FF6F61"
                });
            } else{
                this.miUser = response;
            }
        } catch (msg: any) {
            console.log(msg.error)
        }
    }

    onDeleteUser(msg: string){
        this.router.navigate(['/home'])

        Swal.fire({
        position: "bottom-end",
        text: msg,
        showConfirmButton: false,
        timer: 1500,
        background: "#98FF98"
        });
    }
}
