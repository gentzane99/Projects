import { Component, input } from '@angular/core';
import { RouterLink } from '@angular/router';

@Component({
    selector: 'app-back-to-users-button',
    imports: [RouterLink],
    templateUrl: './back-to-users-button.component.html',
    styleUrl: './back-to-users-button.component.css'
})
export class BackToUsersButtonComponent {
    text = input<string>("Home")
}
