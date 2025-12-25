import { Component, Input, inject } from '@angular/core';
import { IUser } from '../../interfaces/iuser.interface';
import { UsersService } from '../../services/users.service';
import { FormGroup, FormControl, ReactiveFormsModule, Validators, AbstractControl } from '@angular/forms';
import { Router } from '@angular/router';
import Swal from 'sweetalert2';
@Component({
    selector: 'app-user-form',
    imports: [ReactiveFormsModule],
    templateUrl: './user-form.component.html',
    styleUrl: './user-form.component.css',
})
export class UserFormComponent {
    @Input() idUser: string = '';
    userForm: FormGroup;
    userService = inject(UsersService);
    router = inject(Router);
    miUser?: IUser;
    title: string = 'Nuevo';

    constructor() {
        this.userForm = new FormGroup({
            nombre: new FormControl('', [Validators.required, Validators.pattern(/^(?!\s*$).+/)]),
            apellido: new FormControl('', [Validators.required, Validators.pattern(/^(?!\s*$).+/)]),
            email: new FormControl('', [Validators.required, Validators.pattern(/^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/)]),
            imagen: new FormControl('', [Validators.required, this.webImgValidator]),
        }, []);
    }

    ngOnInit() {
        if (this.idUser) {
            this.title = 'Actualizar';
            this.getUser(this.idUser);
        }
    }
 
    async getUser(id: string) {
        try { 
            const response = await this.userService.getById(id);
            if(response.error){
                this.router.navigate(['/home'])
                this.sweetAlertSuccsess("No se ha podido recuperar el usuario", "#FF6F61")
            } else{
                this.miUser = response;
                this.userForm.patchValue({
                    nombre: this.miUser?.first_name,
                    apellido: this.miUser?.last_name,
                    email: this.miUser?.email,
                    imagen: this.miUser?.image,
                    });       
            }
        } catch (msg: any) {
            console.log(msg.error)
        }
    }
    
    //Function to check errors in the controls
    checkControl(controlName: string, errorName: string): boolean | undefined {
        return (this.userForm.get(controlName)?.hasError(errorName) && this.userForm.get(controlName)?.touched);
    }   

    webImgValidator(controlName: AbstractControl): any{
        const url = controlName.value;
        if(!url) return null
        
        //Web page image pattern (does not check the extension)
        const pattern = /^https?:\/\/.+/i
        return pattern.test(url) ? null : {'webImgValidator' : 'La URL debe ser una imagen alojada en internet'}
    }

    async submitForm() {
        try {
            if (this.userForm.value._id) {
                //Update user
                const response: any = await this.userService.update(this.userForm.value);
                if (!response.error) {
                    this.router.navigate(['/home'])
                    this.sweetAlertSuccsess("Usuario actualizado exitosamente", "#98FF98")
                } else{
                    console.log(response)
                }
            } else {
                //New user
                const response: any = await this.userService.insert(this.userForm.value);
                if (!response.error) {
                    this.router.navigate(['/home']);
                    this.sweetAlertSuccsess("Usuario añadido exitosamente", "#98FF98")
                } else{
                    console.log(response)
                }
            }
        } catch (msg: any) {
            console.log(msg.error);
        }
    }

    sweetAlertSuccsess(msg: string, color: string){
        Swal.fire({
            position: "bottom-end",
            text: msg,
            showConfirmButton: false,
            timer: 1500,
            background: color
        });
    }

}
