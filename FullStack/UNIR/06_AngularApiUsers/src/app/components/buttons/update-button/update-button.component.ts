import { Component, input } from '@angular/core';
import { IUser } from '../../../interfaces/iuser.interface';
import { RouterLink } from '@angular/router';

@Component({
    selector: 'app-update-button',
    imports: [RouterLink],
    templateUrl: './update-button.component.html',
    styleUrl: './update-button.component.css'
})
export class UpdateButtonComponent {
    miUser = input<IUser>()
    visible = input<boolean>(true)
}
