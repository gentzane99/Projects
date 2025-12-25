import { Component, input } from '@angular/core';
import { IUser } from '../../../interfaces/iuser.interface';
import { RouterLink } from '@angular/router';

@Component({
    selector: 'app-view-details-button',
    imports: [RouterLink],
    templateUrl: './view-details-button.component.html',
    styleUrl: './view-details-button.component.css'
})
export class ViewDetailsButtonComponent {
    miUser = input<IUser>()
}
